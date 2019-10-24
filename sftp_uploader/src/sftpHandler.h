//
//  sftpHandler.h
//  sftp_uploader
//
//  Created by Stephan Schulz on 2019-10-24.
//

//http://lozano-hemmer.com/transfer/test2.php

#ifndef sftpHandler_h
#define sftpHandler_h
class sftpHandler: public ofThread{
private:
    
public:
    
    struct onePackage {
        string stringToSend;
        
    };
    
    string IP;
    string password;
    string userName;
    string remotePath;
    string scriptPath;
    string localPath;
    string sendString;
    
    ofThreadChannel<onePackage> toSend;
    ofThreadChannel<bool> sentPackage;
    bool bWasSent;
    bool newFrame;
    
    sftpHandler():newFrame(true){
        startThread();
    }
    ~sftpHandler(){
        toSend.close();
        sentPackage.close();
        waitForThread(true);
    }
    
    void setup(){
        // this is our buffer to store the text data
        ofLog()<<"looking for file sftpSettings.txt";
        ofBuffer buffer = ofBufferFromFile("sftpSettings.txt");
        
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
    
    void update(){
        
        newFrame = false;
        while(sentPackage.tryReceive(bWasSent)){
            newFrame = true;
        }
        if(newFrame){
            
        }
        
    }
    
    bool isFrameNew(){
        return newFrame;
    }
    
    void addSFTP(string _sendString){
        
        std::unique_lock<std::mutex> lock(mutex);
        onePackage pack;
        pack.stringToSend = _sendString;
        toSend.send(pack);      
        
        sendString = _sendString;
        
        
    }
    
    void threadedFunction(){
        onePackage temp_onePackage;
        while(toSend.receive(temp_onePackage)){
            
            ofBuffer buf;
            buf.set(temp_onePackage.stringToSend);
            ofBufferToFile(localPath, buf);
            
            //string myScript = "/Users/myname/Desktop/./sftpx mypassword remoteUser@ipAddress ~/Desktop/connections.txt /home/www/myUrl.com/transfer/connections.txt";
            
            string myScript = scriptPath+" "+password+" "+userName+"@"+IP+" "+localPath+" "+remotePath+"/connections.txt";
            
            cout<<myScript<<endl;
            std::system(myScript.c_str());
            
#if __cplusplus>=201103
            sentPackage.send(std::move(true));
#else
            sentPackage.send(true);
#endif
            
        }
        
    }
    
    void draw(int _x, int _y){
        ofPushMatrix();
        ofTranslate(_x,_y);
        int temp_y = 0;
        ofDrawBitmapStringHighlight("sftp upload to IP = "+IP, 10, temp_y+=15);
        
        ofDrawBitmapStringHighlight("123456", 10, temp_y+=15);   
        ofDrawBitmapStringHighlight(sendString, 10, temp_y+=15);    
        ofPopMatrix();
    }
};

#endif /* sftpHandler_h */
