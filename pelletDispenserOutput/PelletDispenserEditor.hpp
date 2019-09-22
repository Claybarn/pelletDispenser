//
//  PelletDispenserEditor.hpp
//  PelletDispenser
//
//  Created by Clayton Barnes on 9/22/19.
//  Copyright © 2019 Clayton Barnes. All rights reserved.
//

#ifndef PelletDispenserEditor_hpp
#define PelletDispenserEditor_hpp

#include <EditorHeaders.h>
#include "PelletDispenser.hpp"
#include <SerialLib.h>



/**
 User interface for the pelletDispenser processor.
 @see PelletDispenser
 */

class PelletDispenserEditor : public GenericEditor,
public ComboBox::Listener,
public Label::Listener

{
public:
    PelletDispenserEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors);
    virtual ~PelletDispenserEditor();
    
    void receivedEvent();
    void buttonEvent(Button* button);
    void labelTextChanged(Label* labelThatHasChanged);
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged);
    
    PelletDispenser* processor;
    
    ofSerial serial;
    
    
private:
    
    ScopedPointer<ComboBox> gateChannelSelector;
    ScopedPointer<ComboBox> deviceSelector;
    ScopedPointer<Button> dispense;
    
    void timerCallback();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PelletDispenserEditor);
    
};



#endif /* PelletDispenserEditor_hpp */
