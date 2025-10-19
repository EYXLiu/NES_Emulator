#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <functional>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace olc
{
    class SOUND
    {
    public:
        // Init / teardown
        static bool InitialiseAudio(unsigned int sampleRate = 44100, unsigned int channels = 1, unsigned int blockSamples = 512)
        {
            if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                std::cerr << "SDL2 Audio Init failed: " << SDL_GetError() << std::endl;
                return false;
            }

            m_sampleRate = sampleRate;
            m_channels = channels;
            m_blockSamples = blockSamples;
            m_blockMemory.resize(blockSamples);

            SDL_AudioSpec spec{};
            spec.freq = m_sampleRate;
            spec.format = AUDIO_S16SYS;
            spec.channels = m_channels;
            spec.samples = m_blockSamples;
            spec.callback = nullptr; 

            m_audioDevice = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);
            if (m_audioDevice == 0) {
                std::cerr << "SDL2 OpenAudioDevice failed: " << SDL_GetError() << std::endl;
                return false;
            }

            SDL_PauseAudioDevice(m_audioDevice, 0);

            m_audioThreadActive = true;
            m_audioThread = std::thread(AudioThread);
            return true;
        }

        static bool DestroyAudio()
        {
            m_audioThreadActive = false;
            if (m_audioThread.joinable())
                m_audioThread.join();

            SDL_CloseAudioDevice(m_audioDevice);
            SDL_QuitSubSystem(SDL_INIT_AUDIO);
            return true;
        }

        // Sample management
        static int LoadAudioSample(const std::string& filename)
        {
            std::ifstream file(filename, std::ios::binary);
            if (!file.is_open()) return -1;

            char riff[4]; file.read(riff, 4); file.seekg(4, std::ios::cur); file.read(riff, 4);
            char fmt[4]; file.read(fmt, 4);
            uint32_t chunkSize; file.read(reinterpret_cast<char*>(&chunkSize), 4);
            file.seekg(chunkSize, std::ios::cur);

            char dataTag[4]; uint32_t dataSize = 0;
            while (!file.eof()) {
                file.read(dataTag, 4); file.read(reinterpret_cast<char*>(&dataSize), 4);
                if (strncmp(dataTag, "data", 4) == 0) break;
                file.seekg(dataSize, std::ios::cur);
            }

            if (file.eof()) return -1;

            AudioSample sample;
            int nSamples = dataSize / sizeof(short);
            sample.samples.resize(nSamples);

            for (int i = 0; i < nSamples; i++) {
                short s; file.read(reinterpret_cast<char*>(&s), sizeof(short));
                sample.samples[i] = s / 32768.0f;
            }

            vecAudioSamples.push_back(sample);
            return vecAudioSamples.size();
        }

        static void PlaySample(int id, bool loop = false)
        {
            if (id <= 0 || id > (int)vecAudioSamples.size()) return;
            sCurrentlyPlayingSample s;
            s.sampleID = id - 1;
            s.loop = loop;
            s.position = 0;
            s.finished = false;
            s.stopFlag = false;
            listActiveSamples.push_back(s);
        }

        static void StopSample(int id)
        {
            for (auto& s : listActiveSamples)
                if (s.sampleID == id - 1) s.stopFlag = true;
        }

        static void StopAll()
        {
            for (auto& s : listActiveSamples) s.stopFlag = true;
        }

        static void SetUserSynthFunction(std::function<float(int,float,float)> func)
        {
            funcUserSynth = func;
        }

    private:
        struct AudioSample { std::vector<float> samples; int channels = 1; };
        struct sCurrentlyPlayingSample { int sampleID=0; long position=0; bool loop=false, finished=false, stopFlag=false; };

        static float GetMixerOutput(int channel, float globalTime, float timeStep)
        {
            float mix = 0.0f;
            for (auto &s : listActiveSamples) {
                if (s.stopFlag) { s.loop=false; s.finished=true; continue; }
                auto &sample = vecAudioSamples[s.sampleID];
                int idx = s.position*sample.channels+channel;
                if (idx < (int)sample.samples.size()) mix += sample.samples[idx];
                s.position++;
                if (s.position >= (long)(sample.samples.size()/sample.channels)) {
                    if (s.loop) s.position=0; else s.finished=true;
                }
            }
            listActiveSamples.remove_if([](const sCurrentlyPlayingSample &s){ return s.finished; });
            if (funcUserSynth) mix += funcUserSynth(channel, globalTime, timeStep);
            return std::clamp(mix, -1.0f, 1.0f);
        }

        static void AudioThread()
        {
            float timeStep = 1.0f / (float)m_sampleRate;
            short maxSample = 32767;
            while (m_audioThreadActive) {
                for(unsigned int i=0;i<m_blockSamples;i+=m_channels){
                    for(unsigned int c=0;c<m_channels;c++){
                        float f = GetMixerOutput(c, m_globalTime, timeStep);
                        m_blockMemory[i+c] = (short)(f*maxSample);
                    }
                    m_globalTime = m_globalTime + timeStep;
                }
                SDL_QueueAudio(m_audioDevice, m_blockMemory.data(), m_blockMemory.size()*sizeof(short));
                SDL_Delay(1);
            }
        }

        // ---- static members (C++17 inline) ----
        inline static std::vector<AudioSample> vecAudioSamples;
        inline static std::list<sCurrentlyPlayingSample> listActiveSamples;
        inline static std::thread m_audioThread;
        inline static std::atomic<bool> m_audioThreadActive{false};
        inline static std::atomic<float> m_globalTime{0.0f};
        inline static std::function<float(int,float,float)> funcUserSynth = nullptr;
        inline static SDL_AudioDeviceID m_audioDevice = 0;
        inline static std::vector<short> m_blockMemory;
        inline static unsigned int m_sampleRate = 0;
        inline static unsigned int m_channels = 0;
        inline static unsigned int m_blockSamples = 0;
    };
}
