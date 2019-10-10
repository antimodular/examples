#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
    // this is our buffer to stroe the text data
    ofLog()<<"looking for file masterIP.txt";
    ofBuffer buffer = ofBufferFromFile("mainIP.txt");
    
    if(buffer.size()) {
        
        int cnt = 0;
        for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
            
            string line = *it;
            
            // copy the line to draw later
            // make sure its not a empty line
            if(line.empty() == false) {
                
                vector<string> split = ofSplitString(line, ":");
                
                if(split.size() >= 2){
                    if(split[0] == "IP") IP = split[1]; 
                    if(split[0] == "userName") userName = split[1];
                    if(split[0] == "password") password = split[1];
                    if(split[0] == "remotePath") remotePath = split[1];
                }
            }
            
            // print out the line
            cout << line << endl;
        }
        
        ofLog()<<"found IP "<<IP<<" user "<<userName<<" passw "<<password<<" remotePath "<<remotePath;
    }

    scriptPath = ofToDataPath("./sftpx");
    localPath = ofToDataPath("uploadFile/connections.txt");

}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if(ofGetElapsedTimef() > 3){
        
        //string myScript = "/Users/stephanschulz/Desktop/./sftpx mypassword remoteUser@ipAddress ~/Desktop/connections.txt /home/www/myUrl.com/transfer/connections.txt";
        
        string myScript = scriptPath+" "+password+" "+userName+"@"+IP+" "+localPath+" "+remotePath+"/connections.txt";
        
        cout<<myScript<<endl;
        std::system(myScript.c_str());
        
        std::exit(1);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapStringHighlight("sftp upload to IP = "+IP, 10, ofGetHeight()/2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
