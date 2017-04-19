#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    song.load("Doom-DaDa.mp3");
    while(!song.isLoaded());
    song.play();
    nBandsToGet = 540;
    
//    loc = ofPoint(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()), ofRandom(0,-500));
    
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
    hue = 255;
    
    
}
float *val;

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSoundUpdate();
    
    val = ofSoundGetSpectrum(nBandsToGet);
    
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
    for (int i = 0;i < nBandsToGet; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.96f;
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }
    
    float time = ofGetElapsedTimef();
    fallWiggle = ofSignedNoise(time * 0.5)*ofRandom(1,5);
    
}

float getX (int deg, int radius) {
    float x = radius * cos(ofDegToRad(deg)) + ofGetWidth()/2;
    return (x);
}

float getY (int deg, int radius) {
    float y = radius * sin(ofDegToRad(deg)) + ofGetHeight()/2;
    return (y);
}


//--------------------------------------------------------------
void ofApp::draw(){
    int r = 100;
    ofBackground(0);
    ofSetColor(255);
    ofNoFill();
    ofSetLineWidth(3);
    ofDrawTriangle(ofGetWidth()/2, ofGetHeight()/2-200, ofGetWidth()/2-200, ofGetHeight()/2+200, ofGetWidth()/2+200, ofGetHeight()/2+200);
    ofDrawLine(ofGetWidth()/2, ofGetHeight()/2-200,ofGetWidth()/2, ofGetHeight()/2-100);
    ofDrawLine(ofGetWidth()/2-200, ofGetHeight()/2+200,ofGetWidth()/2-120, ofGetHeight()/2+150);
    ofDrawLine(ofGetWidth()/2+200, ofGetHeight()/2+200,ofGetWidth()/2+120, ofGetHeight()/2+150);
    
    
    for(int i = 0;i < 80; i ++){
        ofSetColor(255,ofRandom(val[i]*200));
        ofDrawSphere(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()), ofRandom(0,-val[i]*500),val[i]*5);
    }
    

    ofSetLineWidth(5);
    ofSetColor(255,100);
    for(int i = 100; i<460;i++){
        float x1 = getX(i, r);
        float y1 = getY(i, r);
        float x2 = getX(i, r + 150 * fftSmoothed[i]);  // up to 2k larger (theoretically) but it will never get even close
        float y2 = getY(i, r + 150 * fftSmoothed[i]);
        ofDrawLine(x1, y1+50,-100, x2, y2+50,-100);  // we only care about bottom 8th of the spectrum
    }
    
    ofSetLineWidth(0.5);
    for(int i = 160; i<360;i++){
        ofRotate(val[i]*500,ofGetWidth()/2,ofGetHeight()/2+50,-100);
        ofSetColor(255,50);
//        ofDrawRectangle(100+i *2, ofGetHeight()-100, 2, (-1*val[i]*8000));
    }
    ofDrawSphere(ofGetWidth()/2,ofGetHeight()/2+50, -100,50);
    

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
