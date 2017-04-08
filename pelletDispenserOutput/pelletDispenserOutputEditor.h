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

#ifndef __PelletDispenserOUTPUTEDITOR_H_28EB4CC9__
#define __PelletDispenserOUTPUTEDITOR_H_28EB4CC9__


#include <EditorHeaders.h>
#include "PelletDispenserOutput.h"
#include <SerialLib.h>



/**

  User interface for the pelletDispenser processor.

  @see PelletDispenserOutput

*/

class PelletDispenserOutputEditor : public GenericEditor,
                            public ComboBox::Listener,
                            public Label::Listener

{
public:
    PelletDispenserOutputEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors);
    virtual ~PelletDispenserOutputEditor();

    void receivedEvent();
    void buttonEvent(Button* button);
    void labelTextChanged(Label* labelThatHasChanged);
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged);

    PelletDispenserOutput* PelletDispenser;

    ofSerial serial;
    

private:
    
    ScopedPointer<ComboBox> gateChannelSelector;
    ScopedPointer<ComboBox> deviceSelector;
    ScopedPointer<Button> dispense;

    void timerCallback();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PelletDispenserOutputEditor);

};




#endif  // __PelletDispenserOUTPUTEDITOR_H_28EB4CC9__
