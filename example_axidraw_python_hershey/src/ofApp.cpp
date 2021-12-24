#include "ofApp.h"

//to make python 3 with axidraw work inside OF
//install python3 on macos
//install axidraw with pip3
//find install python.framework at Library/Frameworks/Python.framework
//in xcode got to targets -> build phases -> link binary libraries -> + sign -> add other -> now navigate to the framework as shown in the above line

#include <Python/Python.h>
//#include </usr/local/bin/python/Python.h>
///Library/Frameworks/Python.framework
//#include </Applications/of_v0.11.0_osx_release/apps/evaporation_writer/example_python/src/Python3.framework/Versions/3.8/Headers/Python.h>
//--------------------------------------------------------------
void ofApp::setup(){

    //https://python.readthedocs.io/en/v2.7.2/extending/embedding.html
    //https://docs.python.org/3/extending/extending.html#a-simple-example
    //https://docs.python.org/3/c-api/index.html#c-api-index
    //https://docs.python.org/3/extending/embedding.html
    //https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
    Py_Initialize();
//    PyRun_SimpleString("from time import time,ctime\n"
//                       "print 'Today is',ctime(time())\n");
    PyRun_SimpleString("import time\n"
                       "print ('now is : ', time.ctime())\n");

    Py_Finalize();
 
    //https://axidraw.com/doc/py_api/#introduction
    //set color of the font (default is black)
    hersheyFont.setColor(ofColor(0));
 
    current_string = "hello!";
    
    //A3 297 x 420 mm, 11-3/4 x 16-1/2 in
    Py_Initialize();
    string python_str = "";
    python_str += "import time\n";
    python_str += "from pyaxidraw import axidraw\n";
    
    python_str += "ad = axidraw.AxiDraw()\n";
    python_str += "ad.interactive()\n";
    python_str += "ad.options.model = 2\n"; //https://axidraw.com/doc/py_api/#model
    python_str += "ad.options.speed_pendown = "+ofToString(90)+"\n";// Integers from 1 to 110. speed limit for the XY carriage when the pen is down
    python_str += "ad.options.speed_penup = "+ofToString(100)+"\n"; //speed limit for the XY carriage when the pen is up
    
    python_str += "ad.connect()\n";
    
// Change some options, just to show how we do so:
    python_str += "ad.options.units = 1\n"; // 0 inch, 1 cm, 2 mm
    python_str += "ad.options.pen_pos_down = "+ofToString(0)+"\n";
    python_str += "ad.options.pen_pos_up = "+ofToString(60)+"\n";
    python_str += "ad.update()\n";                 // Process changes to options 
    
//    python_str += "ad.moveto(42.0,0)\n";
//    python_str += "ad.moveto(42.0,29.7)\n";
//    python_str += "ad.moveto(0,29.7)\n";
//    python_str += "ad.moveto(0,0)\n";
    
//    python_str += "ad.pendown()\n";
//    python_str += "time.sleep(1.0)\n";
//    python_str += "ad.penup()\n";
    
    python_str += hersheyFont.getPath_asPythonString(current_string, "ad.", 0, 6, 0.3);
    
    python_str += "ad.moveto(0,0)\n"; //Return home
    python_str += "ad.disconnect()\n";
    
    cout<<"python_str:"<<endl;
    cout<<python_str<<endl;
    
    PyRun_SimpleString(python_str.c_str());
    Py_Finalize();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    ofPushMatrix();
    ofTranslate(0,ofGetHeight()/2);
    ofPath current_path = hersheyFont.getPath(current_string,10,10,1);
    ofSetColor(255);
    current_path.draw();
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == '1'){
        //https://axidraw.com/doc/py_api/#installation
        /*
         from pyaxidraw import axidraw   # import module
         ad = axidraw.AxiDraw()          # Initialize class
         ad.interactive()                # Enter interactive context
         ad.connect()                    # Open serial port to AxiDraw 
                                         # Absolute moves follow:
         ad.moveto(1,1)                  # Pen-up move to (1 inch, 1 inch)
         ad.lineto(2,1)                  # Pen-down move, to (2 inch, 1 inch)
         ad.moveto(0,0)                  # Pen-up move, back to origin.
         ad.disconnect()                 # Close serial port to AxiDraw
         */
        
        Py_Initialize();
        PyRun_SimpleString("from pyaxidraw import axidraw\n"
                           "ad = axidraw.AxiDraw()\n"
                           "ad.interactive()\n"
                           "ad.connect()\n"
                           "ad.moveto(1,1)\n"
                           "ad.lineto(2,1)\n"
                           "ad.moveto(0,0)\n"
                           "ad.disconnect()\n"
                           );
        Py_Finalize();
    }
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
