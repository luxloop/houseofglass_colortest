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
    debug = false;
    easeRange = 2000;
    
    currentMode = LINEAR;
    //manualCounter = ULLONG_MAX;
    manualCounter = 0;
    
    
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
    
    switch (currentMode) {
        case LINEAR:
            if (currentIndex < timeList.size()-1) {
                if (currentIndex == 0) {
                    timeRange = timeList[0];
                    lerpPerc = (long double) ellapsed/timeRange;
                } else {
                    timeRange = timeList[currentIndex] - timeList[currentIndex-1];
                    lerpPerc = (long double) (ellapsed - timeList[currentIndex-1])/timeRange;
                }
                
                if (ellapsed < timeList[currentIndex]) {
                    //screenColor = colorList[currentIndex];
                    screenColor = colorList[currentIndex].getLerped(colorList[currentIndex+1], lerpPerc);
                } else {
                    currentIndex++;
                }
            } else {
                screenColor = colorList[colorList.size()-1];
            }
            break;
            
        case EASEINOUT:
            if (currentIndex < timeList.size()-1) {
                if (currentIndex == 0) {
                    timeRange = timeList[0];
                } else {
                    timeRange = timeList[currentIndex] - timeList[currentIndex-1];
                }
                
                if (timeRange > easeRange) {
                    timeRange = easeRange;
                    if (ellapsed < timeList[currentIndex]-timeRange) {
                        lerpPerc = 0.0f;
                    } else {
                        lerpPerc = (long double) (ellapsed - (timeList[currentIndex]-timeRange))/timeRange;
//                        lerpPerc = 1.0f;
                    }
                } else {
                    if (currentIndex == 0) {
                        lerpPerc = (long double) ellapsed/timeRange;
                    } else {
                        lerpPerc = (long double) (ellapsed - timeList[currentIndex-1])/timeRange;
                    }
                }
                
                if (ellapsed < timeList[currentIndex]) {
                    //screenColor = colorList[currentIndex];
                    screenColor = colorList[currentIndex].getLerped(colorList[currentIndex+1], lerpPerc);
                } else {
                    currentIndex++;
                }
            } else {
                screenColor = colorList[colorList.size()-1];
            }
            break;
            
        case MANUAL:
            if (currentIndex < timeList.size()-1) {
                if (ellapsed - manualCounter < easeRange && manualCounter != 0) {
                    lerpPerc = (long double) (ellapsed-manualCounter)/easeRange;
                    screenColor = colorList[currentIndex].getLerped(colorList[currentIndex+1], lerpPerc);
                } else if (manualCounter == 0) {
                    screenColor = colorList[currentIndex];
                } else {
                    screenColor = colorList[currentIndex+1];
                }
            } else {
                screenColor = colorList[colorList.size()-1];
            }
            break;
            
        default:
            break;
    }
    
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(screenColor);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    if (debug) {
        ofSetColor(0, 0, 0);
        string mode;
        switch (currentMode) {
            case LINEAR:
            default:
                mode = "LINEAR";
                break;
            
            case EASEINOUT:
                mode = "EASED";
                break;
                
            case MANUAL:
                mode = "MANUAL";
                break;
            
        }
        ofDrawBitmapString(mode, 20, ofGetHeight()-60);
        ofDrawBitmapString("current index: " + ofToString(currentIndex), 20, ofGetHeight()-50);
        ofDrawBitmapString("range: " + ofToString(timeRange), 20, ofGetHeight()-40);
        
        ofDrawBitmapString("elapsed time: " + ofToString(ofGetElapsedTimeMillis()), 20, ofGetHeight()-20);
        ofDrawBitmapString("interpolation: " + ofToString(lerpPerc,1) + "%", 20, ofGetHeight()-10);
        ofSetColor(255);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '/':
            debug = !debug;
            break;
            
        case '1':
            currentMode = LINEAR;
            break;
            
        case '2':
            currentMode = EASEINOUT;
            break;
            
        case '3':
            currentMode = MANUAL;
            break;
            
        case ' ':
            if (currentMode == MANUAL) {
                if (currentIndex < timeList.size()-1 && manualCounter != 0) {
                    currentIndex++;
                }
                manualCounter = ofGetElapsedTimeMillis();
                
            }
            break;
            
        default:
            break;
    }
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
