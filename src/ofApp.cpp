#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    colorscript = ofBufferFromFile("colorscript.txt");

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 0, 0);
    ofDrawBitmapString(ofToString(ofGetElapsedTimeMillis()), 20,ofGetHeight()-20);
    ofSetColor(255);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    string s = colorscript.getNextLine();
    if (s == "") {
        cout << "zilch" << endl;
    } else {
        vector<string> pieces = ofSplitString(s, " ");
        
        unsigned long long millis;
        if (ofIsStringInString(pieces[0], ":")) {
            vector<string> timeStr = ofSplitString(pieces[0], ":");
            int minutes = ofToInt(timeStr[0]);
            int seconds = ofToInt(timeStr[1]);
            millis = (unsigned long long)((seconds + (minutes * 60)) * 1000);
        } else {
            millis = (unsigned long long)(ofToInt(pieces[0]) * 1000);
        }
        
        cout << millis << " | " << pieces[1] << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
