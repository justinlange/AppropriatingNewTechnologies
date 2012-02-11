#include "ofApp.h"

// save http://i.imgur.com/ym71g.gif as data/body.gif

//Coding advice: make fewer decisions so you can make fewer mistakes

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofVideoPlayer body;
	body.loadMovie("body.gif");
	int n = body.getTotalNumFrames();  //check how many frames there are  
	for(int i = 0; i < n; i++) {
		// load and save the current frame
		body.setFrame(i);
		slices.push_back(body.getPixelsRef());  //getPixelsRef allows you to easily convert between video and image, by just treating the pixels...   sor of like ofImage(body);... 
        
		// process each slice so the brightness determines the alpha
		slices.back().setImageType(OF_IMAGE_COLOR_ALPHA); // RGB -> RGBA  // just tells you what the last image is...
		
        //this section makes the last slice transparent
        ofPixels& pix = slices.back().getPixelsRef(); //the & character creates a reference or "alias", kind of a soft link to a file. The official name is reference. Pix now referes to the pixils on the back of the slices vector. 
        
		for(int y = 0; y < pix.getHeight(); y++) {
			for(int x = 0; x < pix.getWidth(); x++) {
				ofColor cur = pix.getColor(x, y);
				cur.a = cur.getBrightness();
				pix.setColor(x, y, cur);
			}
		}
		// update the ofImage (upload ofPixels to ofTexture)
		slices.back().update();
	}
	ofEnableAlphaBlending();
}  

void ofApp::update() {
}

void ofApp::draw() {
	ofBackground(0);
	cam.begin();
	ofSetColor(255, 64); // make everything more transparent
	float spacing = 8;
    
    
	ofTranslate(-slices[0].getWidth() / 2, -slices[0].getHeight() / 2, -spacing * slices.size() / 2); // center things
	for(int i = 0; i < slices.size(); i++) {
		ofPushMatrix();
		
		// space the slices out evenly on the z axis
		ofTranslate(0, 0, i * spacing);
		
		// jiggle things
		float noiseOffset = ofGetElapsedTimef() + i;
		float noiseScale = 10;
		ofTranslate(ofSignedNoise(noiseOffset, 0) * noiseScale, ofSignedNoise(0, noiseOffset) * noiseScale, 0);
		
		slices[i].draw(0, 0);
		ofPopMatrix();
	}
	cam.end();
}
