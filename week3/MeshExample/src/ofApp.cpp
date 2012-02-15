#include "ofApp.h"

//just loading in mesh this time

int currentFrame = 1;
int previousFrame = 0;
string frameResult;
int skip;	
int width;
int height;


void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	mesh.addVertex(a);
	mesh.addVertex(b);
	mesh.addVertex(c);
}

void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
	addFace(mesh, a, b, c);
	addFace(mesh, a, c, d);
}

ofVec3f getVertexFromImg(ofImage& img, int x, int y) {   
	ofColor color = img.getColor(x, y);
	if(color.a > 0) {
		float z = ofMap(color.a, 0, 255, -480, 480);
		return ofVec3f(x - img.getWidth() / 2, y - img.getHeight() / 2, z);
	} else {
		return ofVec3f(0, 0, 0);
	}
}

void ofApp::setup() {
	ofSetVerticalSync(true);
	img.loadImage("1.png");
	
	mesh.setMode(OF_PRIMITIVE_TRIANGLES); //rather than points
    skip = 5;	
	width = img.getWidth();
	height = img.getHeight();
	ofVec3f zero(0, 0, 0);

	
	// even points can overlap with each other, let's avoid that
	glEnable(GL_DEPTH_TEST);  //don't really notice, because we're in wireframe
}

void ofApp::update() {
    
    
    
     //if space bar is pressed, increment playback number
     
    if(ofGetKeyPressed('p')) {
        skip++;
    }
    if(ofGetKeyPressed('o') && skip >= 1) {
        skip--;
    }

    
     if(ofGetKeyPressed(' ')) {
         if(currentFrame < 42){
             currentFrame++;
         }else{
             currentFrame = 1;
         }
         
     ostringstream fileNameToSave;
     fileNameToSave << currentFrame << ".png";
         frameResult = fileNameToSave.str(); 
         img.loadImage(frameResult);
         mesh.clear();
         
         for(int y = 0; y < height - skip; y += skip) {
             // we need to skip so that the wireframe actually shows something
             
             for(int x = 0; x < width - skip; x += skip) {
                 
                 // this is kind of like quadrants
                 
                 ofVec3f nw = getVertexFromImg(img, x, y);
                 ofVec3f ne = getVertexFromImg(img, x + skip, y);
                 ofVec3f sw = getVertexFromImg(img, x, y + skip);
                 ofVec3f se = getVertexFromImg(img, x + skip, y + skip);
                 if(nw != 0 && ne != 0 && sw != 0 && se != 0) {  //this line checks for bad data
                     addFace(mesh, nw, ne, se, sw); //so long as nothing is zero.... otherwise vertices point to front of screen
                     
                 }
             }
         }

     }
     

	
}

void ofApp::draw() {
	ofBackground(0);
	cam.begin();
	ofScale(1, -1, 1); // make y point down
	mesh.drawWireframe();
	cam.end();
}