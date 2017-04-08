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

#include "PelletDispenserOutputEditor.h"
#include <stdio.h>


PelletDispenserOutputEditor::PelletDispenserOutputEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors=true)
    : GenericEditor(parentNode, useDefaultParameterEditors)

{
    desiredWidth = 250;

    PelletDispenser = (PelletDispenserOutput*) parentNode;

    vector <ofSerialDeviceInfo> devices = serial.getDeviceList();
    deviceSelector = new ComboBox();
    deviceSelector->setBounds(80,85,125,20);
    deviceSelector->addListener(this);
    deviceSelector->addItem("Device",1);
    
    for (int i = 0; i < devices.size(); i++)
    {
        deviceSelector->addItem(devices[i].getDevicePath(),i+2);
    }
    deviceSelector->setSelectedId(1, dontSendNotification);
    addAndMakeVisible(deviceSelector);
    
    gateChannelSelector = new ComboBox();
    gateChannelSelector->setBounds(80,55,55,20);
    gateChannelSelector->addListener(this);
    gateChannelSelector->addItem("Gate",1);
    for (int i = 0; i < 16; i++)
        gateChannelSelector->addItem(String(i+1),i+2); // start numbering at one for
    // user-visible channels
    gateChannelSelector->setSelectedId(1, dontSendNotification);
    addAndMakeVisible(gateChannelSelector);
    
    dispense = new UtilityButton("Dispense", Font("Default", 15, Font::plain));
    dispense->setBounds(10, 50, 60, 40); //Set position and size (X, Y, XSize, YSize)
    dispense->addListener(this);
    dispense->setClickingTogglesState(false);
    dispense->setTooltip("Press to dispense a pellet, for debugging purposes");
    addAndMakeVisible(dispense);
}

PelletDispenserOutputEditor::~PelletDispenserOutputEditor()
{
}

void PelletDispenserOutputEditor::receivedEvent()
{

}

void PelletDispenserOutputEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == gateChannelSelector)
        PelletDispenser->setGateChannel(gateChannelSelector->getSelectedId()-1);
    else if(comboBoxThatHasChanged == deviceSelector)
            PelletDispenser->setDevice(comboBoxThatHasChanged->getText());
    
}
void PelletDispenserOutputEditor::timerCallback()
{
}

void PelletDispenserOutputEditor::buttonEvent(Button* button){
    if (button == dispense)
    {
        PelletDispenser->dispense();
        
    }
}

void PelletDispenserOutputEditor::labelTextChanged(Label* labelThatHasChanged){
};
