//
//  PelletDispenserEditor.cpp
//  PelletDispenser
//
//  Created by Clayton Barnes on 9/22/19.
//  Copyright © 2019 Clayton Barnes. All rights reserved.
//

#include "PelletDispenserEditor.hpp"

#include <stdio.h>


PelletDispenserEditor::PelletDispenserEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors=true)
: GenericEditor(parentNode, useDefaultParameterEditors)

{
    desiredWidth = 250;
    
    processor =  (PelletDispenser*) getProcessor();
    
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

PelletDispenserEditor::~PelletDispenserEditor()
{
}

void PelletDispenserEditor::receivedEvent()
{
    
}

void PelletDispenserEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == gateChannelSelector)
        processor->setGateChannel(gateChannelSelector->getSelectedId()-1);
    else if(comboBoxThatHasChanged == deviceSelector)
        processor->setDevice(comboBoxThatHasChanged->getText());
    
}
void PelletDispenserEditor::timerCallback()
{
}

void PelletDispenserEditor::buttonEvent(Button* button){
    if (button == dispense)
    {
        processor->addToOnBuffer();
        
    }
}

void PelletDispenserEditor::labelTextChanged(Label* labelThatHasChanged){
};
