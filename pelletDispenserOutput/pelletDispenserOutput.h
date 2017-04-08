/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2014 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __PelletDispenserOUTPUT_H_F7BDA585__
#define __PelletDispenserOUTPUT_H_F7BDA585__

#include <SerialLib.h>
#include <ProcessorHeaders.h>




/**
Establishes interface between OE and pelletDispenser Sketch. Can respond to events.

*/

class PelletDispenserOutput : public GenericProcessor
{
public:

    PelletDispenserOutput();
    ~PelletDispenserOutput();

    /** Searches for events and triggers the PelletDispenser output when appropriate. */
    void process(AudioSampleBuffer& buffer, MidiBuffer& events);

    /** Currently unused. Future uses may include changing the TTL trigger channel
    or the output channel of the PelletDispenser. */
    void setParameter(int parameterIndex, float newValue);

    /** Convenient interface for responding to incoming events. */
    void handleEvent(int eventType, MidiMessage& event, int sampleNum);

    /** Called immediately prior to the start of data acquisition. */
    bool enable();

    /** Called immediately after the end of data acquisition. */
    bool disable();

    /** Creates the PelletDispenserOutputEditor. */
    AudioProcessorEditor* createEditor();

    /** Defines the PelletDispenserOutput processor as a sink. */
    bool isSink()
    {
        return true;
    }

    void setGateChannel(int);
    void setDevice(String deviceString);
    void dispense();
    
    int outputChannel;
    int inputChannel;
    int gateChannel;

private:

    
    ofSerial _port;
    
    unsigned int onBuffer = 0;
    bool state;
    bool acquisitionIsActive;
    bool deviceSelected;
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PelletDispenserOutput);

};




#endif  // __PelletDispenserOUTPUT_H_F7BDA585__
