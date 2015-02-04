#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofBuffer colorscript;
    ofColor screenColor;
    vector<unsigned long long> timeList;
    vector<ofColor> colorList;
    vector<string> textList;
    int currentIndex;
    int easeRange;
    
    unsigned long long timeRange;
    float lerpPerc;
    
    bool debug;
    bool showText;
    
    enum modes {
        LINEAR,
        EASEINOUT,
        MANUAL
    };
    
    modes currentMode;
    
    unsigned long long manualCounter;
		
};
