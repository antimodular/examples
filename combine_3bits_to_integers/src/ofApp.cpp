#include "ofApp.h"

int speakerAmout = 1022;
int speakerStates[1022];

int selectedSpeaker = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    
    for(int i=0; i<speakerAmout;i++){
        speakerStates[i] = 0;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofPushMatrix();
    ofTranslate(10,10);
    
  
    
    ofSetColor(255);
    
       
    process_speakers(18); //1024);

        
    ofPopMatrix();
    
     ofSetColor(0);
    ofDrawBitmapString("use left/right arrow keys to select 3bit set ",10,300);
    ofDrawBitmapString("use up/down arrow keys to set bits ",10,320);


}

void ofApp::process_speakers(int _amt){
    //https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
   
    int y = 0;
    int h = 20;
    
    int speakerAmount = _amt;
    int bitsPerSpeaker = 3;
    int totalBits = speakerAmount * bitsPerSpeaker;
    int intAmount = ceil(totalBits / 32.0);
    ofLog()<<"speakerAmount "<<speakerAmount<<" intAmount "<<intAmount<<" speakerAmount * bitsPerSpeaker  "<<(speakerAmount * bitsPerSpeaker )<<" , "<<(speakerAmount * bitsPerSpeaker / 32.0);
    
    ofDrawBitmapString("speaker amount "+ofToString(_amt),0,y+=h);
    ofDrawBitmapString(ofToString(selectedSpeaker),96 + 32*8*intAmount - selectedSpeaker*bitsPerSpeaker*8, y+=h);
    ofNoFill();
    ofDrawRectangle(96 + 32*8*intAmount - selectedSpeaker*bitsPerSpeaker*8, 0, bitsPerSpeaker*8, 300);  

    
    unsigned int allStatesAsInts[intAmount];
     for(int i=0; i<intAmount;i++){
         allStatesAsInts[i] = 0;
     }
    int nth_bit = 0;
    int intIndex = 0;
    //loop through all i speakers
    for(int i=0; i<speakerAmount;i++){
        for(int j=0; j<bitsPerSpeaker;j++){
            int bit = (speakerStates[i] >> j) & 1U;
            
            unsigned long newbit = !!bit;    // also booleanize to force 0 or 1
            allStatesAsInts[intIndex] ^= (-newbit ^ allStatesAsInts[intIndex]) & (1UL << nth_bit);
            
            nth_bit++;
            if(nth_bit >= 32){
                nth_bit = 0;
                intIndex++;
            }
            
        }
    }
    
    string binaryStrings[intAmount];
    


    ofSetColor(255);
    
    //display the _amt speaker's 8 possible states
    string temp_str;    
    ofDrawBitmapString("speakerStates     "+ temp_str,0,y+=h);
    int x = 120 + 32*8 *intAmount;
    for(int i=0; i<speakerAmount;i++){
        x -= bitsPerSpeaker * 8;
        
        if(i != selectedSpeaker){
            ofSetColor(255);
        }
        else{
            ofSetColor(0);
            int overall_startBit = selectedSpeaker * 3;
            int local_startBit = overall_startBit % 32;
            int overall_startInt = overall_startBit / 32;
            
//            int bit0 = (allStatesAsInts[overall_startInt] >> local_startBit) & 1U;
//            int bit1 = (allStatesAsInts[overall_startInt] >> (local_startBit+1)) & 1U;
//            int bit2 = (allStatesAsInts[overall_startInt] >> (local_startBit+2)) & 1U;
            
//            ofDrawBitmapString(ofToString(bit2) + ":"+ofToString(bit1) + ":"+ofToString(bit0),x,y+115);
            ofDrawBitmapString(ofToString(overall_startBit) + "  ",x,y+130);
            ofDrawBitmapString(ofToString(local_startBit) + "  ",x,y+145);
            ofDrawBitmapString(ofToString(overall_startInt) + "  ",x,y+160);

            
            int nth_bit = local_startBit;
            int intIndex = overall_startInt;
            //loop through all i speakers
            
            int result_int = 0;
            for(int j=0; j<(3);j++){
                int bit = (allStatesAsInts[intIndex] >> nth_bit) & 1U;
                
                 ofDrawBitmapString(ofToString(bit),x+(3*15) - (j*15),y+115);
                
                 result_int = result_int & ~(1 << j) | (bit << j);
                
                nth_bit++;
                if(nth_bit >= 32){
                    nth_bit = 0;
                    intIndex++;
                }
                
            }
            
            ofDrawBitmapString(ofToString(result_int) + "  ",x,y+190);
            
        }
        ofDrawBitmapString(ofToString(speakerStates[i]) + "  ",x,y);
        
        
       
        
    }
    
    x = 0;
    ofSetColor(255);
    ofDrawBitmapString("binaryStrings  ",x,y+= h);
    x = 120 + 32*8 *intAmount;
    for(int i=0; i<intAmount;i++){
        x -=32*8;
        string temp_binaryString = ofToBinary(allStatesAsInts[i]);
        ofDrawBitmapString(temp_binaryString,x,y+= h);
    }
    
    // resulting integer
    x = 0;
    ofDrawBitmapString("result int ",x,y+= h); 
    x = 120 + 32*8 *intAmount;
    for(int i=0; i<intAmount;i++){
        x -=32*8;
        ofDrawBitmapString(ofToString(allStatesAsInts[i]),x,y+=h);
    }
    
      
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if( key == OF_KEY_RIGHT){
        selectedSpeaker--;
        if(selectedSpeaker < 0) selectedSpeaker = speakerAmout-1;
    }
    if( key == OF_KEY_LEFT){
        selectedSpeaker++;
        if(selectedSpeaker >= speakerAmout) selectedSpeaker = 0;
    }

    if( key == OF_KEY_UP){
        speakerStates[selectedSpeaker] ++;
        speakerStates[selectedSpeaker] %= 8;
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
