//
//  PelletDispenser.hpp
//  PelletDispenser
//
//  Created by Clayton Barnes on 9/22/19.
//  Copyright © 2019 Clayton Barnes. All rights reserved.
//

#ifndef PelletDispenser_hpp
#define PelletDispenser_hpp


#include <SerialLib.h>
#include <ProcessorHeaders.h>




/**
 Establishes interface between OE and pelletDispenser Sketch. Can respond to events.
 */

class PelletDispenser : public GenericProcessor
{
public:
    
    PelletDispenser();
    ~PelletDispenser();
    
    /** Searches for events and triggers the PelletDispenser output when appropriate. */
    //void process(AudioSampleBuffer& buffer, MidiBuffer& events);
    void process(AudioSampleBuffer& buffer) override;
    /** Currently unused. Future uses may include changing the TTL trigger channel
     or the output channel of the PelletDispenser. */
    void setParameter(int parameterIndex, float newValue);
    
    /** Convenient interface for responding to incoming events. */
    void handleEvent(int eventType, MidiMessage& event, int sampleNum);
    
    /** Called immediately prior to the start of data acquisition. */
    bool enable();
    
    /** Called immediately after the end of data acquisition. */
    bool disable();
    
    /** Creates the PelletDispenserEditor. */
    AudioProcessorEditor* createEditor();
    
   
    
    void setGateChannel(int);
    void setDevice(String deviceString);
    void dispense();
    
    void createEventChannels();

    void addToOnBuffer();
    
private:
    Array<const EventChannel*> moduleEventChannels;
    int outputChannel;
    int inputChannel;
    int gateChannel;
    ofSerial _port;
    
    unsigned int onBuffer = 0;
    bool state;
    bool acquisitionIsActive;
    bool deviceSelected;
    int data = 1;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PelletDispenser);
    
};

#endif /* PelletDispenser_hpp */
