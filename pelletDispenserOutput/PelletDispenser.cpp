//
//  PelletDispenser.cpp
//  PelletDispenser
//
//  Created by Clayton Barnes on 9/22/19.
//  Copyright © 2019 Clayton Barnes. All rights reserved.
//

#include "PelletDispenser.hpp"
#include "PelletDispenserEditor.hpp"

#include <stdio.h>

PelletDispenser::PelletDispenser()
: GenericProcessor("PelletDispenser"), outputChannel(13), inputChannel(-1), state(true), acquisitionIsActive(false), deviceSelected(false)
{
}

PelletDispenser::~PelletDispenser()
{
    
}

AudioProcessorEditor* PelletDispenser::createEditor()
{
    editor = new PelletDispenserEditor(this, true);
    return editor;
}

void PelletDispenser::setDevice(String devName)
{
    
    if (!acquisitionIsActive)
    {
        
        if(_port.setup(devName.toStdString(), 9600))
            CoreServices::sendStatusMessage(("Pellet dispenser initialized at" + devName));
    }
}

void PelletDispenser::handleEvent(int eventType, MidiMessage& event, int sampleNum)
{
    if (eventType == EventChannel::TTL)
    {
        const uint8* dataptr = event.getRawData();
        int eventId = *(dataptr+2);
        int eventChannel = *(dataptr+3);
        
        if (eventChannel == gateChannel)
        {
            if (eventId == 1)
            {
                state = true;
            } else {
                state = false;
            }
        }
        
        if (state)
        {
            if (inputChannel == -1 || eventChannel == inputChannel)
            {
                if (eventId == 0)
                {
                    
                }
                else
                {
                    onBuffer +=1;
                }
            }
        }
        
        
    }
    
}

void PelletDispenser::setParameter(int parameterIndex, float newValue)
{
    
    
    if (parameterIndex == 0){
        outputChannel = (int) newValue;
    }
    else if (parameterIndex == 1){
        inputChannel = (int) newValue;
    }
    else if (parameterIndex == 2){
        gateChannel = (int) newValue;
        if (gateChannel == -1)
            state = true;
        else
            state = false;
    }
}


void PelletDispenser::setGateChannel(int chan)
{
    setParameter(2, chan-1);
}

bool PelletDispenser::enable()
{
    acquisitionIsActive = true;
    return deviceSelected;
}

bool PelletDispenser::disable()
{
    acquisitionIsActive = false;
    return true;
}

void PelletDispenser::process(AudioSampleBuffer& buffer)
{
    
    checkForEvents(true);
    
    for (onBuffer; onBuffer > 0; onBuffer--) {

        TTLEventPtr event = TTLEvent::createTTLEvent(moduleEventChannels[0], getTimestamp(0),
                                                     &data, sizeof(int), 0);

        addEvent(moduleEventChannels[0], event, 0);
        dispense();

    }
   
}
void PelletDispenser::dispense(){
    _port.writeByte('1');
}

void PelletDispenser::createEventChannels(){
    
    moduleEventChannels.clear();
    
    const DataChannel* in = getDataChannel(0);
    EventChannel* ev = new EventChannel(EventChannel::TTL, 1, 1, (in) ? in->getSampleRate() : CoreServices::getGlobalSampleRate(), this);
    
    
    ev->setName("Pellet Dispenser TTL");
    ev->setDescription("Sent when byte is sent to trigger arduino");
    String identifier = "onTrig.emit.";
    String typeDesc = "onTrig";
    ev->setIdentifier(identifier);
    eventChannelArray.add(ev);
    moduleEventChannels.add(ev);
}

void PelletDispenser::addToOnBuffer(){
    onBuffer+=1;
}
