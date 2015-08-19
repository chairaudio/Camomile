/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PdWrapper.h"

#include <set>
#include <memory>

using namespace std;
using namespace pd;

class CamomileAudioProcessor  : public AudioProcessor
{
public:
    class Listener;
private:
    shared_ptr<Instance>  m_pd;
    weak_ptr<Patch>       m_patch;
    set<Listener*>        m_listeners;
    mutable mutex         m_mutex;
    
public:
    CamomileAudioProcessor();
    ~CamomileAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock(AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override {return true;};

    const String getName() const override {return String(JucePlugin_Name);};

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName(int index) const override {return String(index + 1);}
    const String getOutputChannelName(int index) const override {return String(index + 1);}
    bool isInputChannelStereoPair(int index) const override {return false;}
    bool isOutputChannelStereoPair(int index) const override {return false;}

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override {return false;}
    double getTailLengthSeconds() const override {return 0.0;}

    int getNumPrograms() override {return 1;}
    int getCurrentProgram() override {return 0;}
    void setCurrentProgram(int index) override {}
    const String getProgramName(int index) override {return String();}
    void changeProgramName(int index, const String& newName) override {}

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    void loadPatch(const juce::File& file);
    inline shared_ptr<const Patch> getPatch() const noexcept {return m_patch.lock();}
    inline shared_ptr<Patch> getPatch() noexcept {return m_patch.lock();}
    
    // ================================================================================ //
    //                                      LISTENER                                    //
    // ================================================================================ //
    
    void addListener(Listener* listener)
    {
        if(listener)
        {
            lock_guard<mutex> guard(m_mutex);
            m_listeners.insert(listener);
        }
    }
    
    void removeListener(Listener* listener)
    {
        if(listener)
        {
            lock_guard<mutex> guard(m_mutex);
            m_listeners.erase(listener);
        }
    }
    
    vector<Listener*> getListeners() const noexcept
    {
        lock_guard<mutex> guard(m_mutex);
        return vector<Listener*>(m_listeners.begin(), m_listeners.end());
    }
    
    class Listener
    {
    public:
        inline Listener() {}
        
        inline virtual ~Listener() {}
        
        virtual void patchChanged() = 0;
    };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
