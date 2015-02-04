#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    colorscript = ofBufferFromFile("colorscript.txt");
    screenColor = ofColor(0,0,0);
    timeList.clear();
    colorList.clear();
    currentIndex = 0;
    timeRange = 0;
    lerpPerc = 0.0f;
    
    
    string data = colorscript.getText();
    
    vector<string> s = ofSplitString(data, "\n");
    
    for (int i = 0; i < s.size(); i++) {
        //cout << s[i] << endl;
        if (s[i] == "") {
            cout << "zilch" << endl;
        } else {
            vector<string> pieces = ofSplitString(s[i], " ");
            
            unsigned long long millis;
            if (ofIsStringInString(pieces[0], ":")) {
                vector<string> timeStr = ofSplitString(pieces[0], ":");
                int minutes = ofToInt(timeStr[0]);
                int seconds = ofToInt(timeStr[1]);
                millis = (unsigned long long)((seconds + (minutes * 60)) * 1000);
                timeList.push_back(millis);
            } else {
                millis = (unsigned long long)(ofToInt(pieces[0]) * 1000);
                timeList.push_back(millis);
            }
            
            vector<string> colorData = ofSplitString(pieces[1], ",");
            
            ofColor newColor;
            newColor.r = ofToInt(colorData[0]);
            newColor.g = ofToInt(colorData[1]);
            newColor.b = ofToInt(colorData[2]);
            
            colorList.push_back(newColor);
            
            cout << millis << " | " << pieces[1] << endl;
        }
    }
    if (timeList.size() != colorList.size()) {
        cout << "Lists don't match up!" << endl;
        exit();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    unsigned long long ellapsed = ofGetElapsedTimeMillis();
    
    if (currentIndex < timeList.size()-1) {
        if (currentIndex == 0) {
            timeRange = timeList[0];
            lerpPerc = (long double) ellapsed/timeRange;
        } else {
            timeRange = timeList[currentIndex] - timeList[currentIndex-1];
            lerpPerc = (long double) (ellapsed - timeList[currentIndex-1])/timeRange;
        }
//        lerpPerc = (float) ellapsed/timeRange;
        
        if (ellapsed < timeList[currentIndex]) {
            //screenColor = colorList[currentIndex];
            screenColor = colorList[currentIndex].getLerped(colorList[currentIndex+1], lerpPerc);
        } else {
            currentIndex++;
        }
    } else {
        screenColor = colorList[colorList.size()-1];
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(screenColor);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("current index: " + ofToString(currentIndex), 20,ofGetHeight()-50);
    ofDrawBitmapString("range: " + ofToString(timeRange), 20,ofGetHeight()-40);
    
    ofDrawBitmapString(ofToString(ofGetElapsedTimeMillis()), 20,ofGetHeight()-20);
    ofDrawBitmapString(ofToString(lerpPerc,3), 20,ofGetHeight()-10);
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
    /*
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
        
        vector<string> colorData = ofSplitString(pieces[1], ",");
        
        ofColor newColor;
        newColor.r = ofToInt(colorData[0]);
        newColor.g = ofToInt(colorData[1]);
        newColor.b = ofToInt(colorData[2]);
        
        screenColor = newColor;
        
        cout << millis << " | " << pieces[1] << endl;
    }
    //*/
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
