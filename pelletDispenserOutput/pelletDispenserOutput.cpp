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

#include "PelletDispenserOutput.h"
#include "PelletDispenserOutputEditor.h"

#include <stdio.h>

PelletDispenserOutput::PelletDispenserOutput()
	: GenericProcessor("PelletDispenser Output"), outputChannel(13), inputChannel(-1), state(true), acquisitionIsActive(false), deviceSelected(false)
{
}

PelletDispenserOutput::~PelletDispenserOutput()
{

}

AudioProcessorEditor* PelletDispenserOutput::createEditor()
{
    editor = new PelletDispenserOutputEditor(this, true);
    return editor;
}

void PelletDispenserOutput::setDevice(String devName)
{

    if (!acquisitionIsActive)
    {
        
        if(_port.setup(devName.toStdString(), 9600))
            CoreServices::sendStatusMessage(("Pellet dispenser initialized at" + devName));
       }
}

void PelletDispenserOutput::handleEvent(int eventType, MidiMessage& event, int sampleNum)
{
    if (eventType == TTL)
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

void PelletDispenserOutput::setParameter(int parameterIndex, float newValue)
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


void PelletDispenserOutput::setGateChannel(int chan)
{
    setParameter(2, chan-1);
}

bool PelletDispenserOutput::enable()
{
    acquisitionIsActive = true;
	return deviceSelected;
}

bool PelletDispenserOutput::disable()
{
    acquisitionIsActive = false;
	return true;
}

void PelletDispenserOutput::process(AudioSampleBuffer& buffer,
                            MidiBuffer& events)
{

    checkForEvents(events);

    for (onBuffer; onBuffer > 0; onBuffer--) {
        dispense();
    }
}
void PelletDispenserOutput::dispense(){
    _port.writeByte('1');
}
