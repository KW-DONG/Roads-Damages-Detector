## PRD (Product requirements document)
## Product Overview
### Product Name: 
Roads Damages Detector
### Product Description: 
A mobile application that uses roads damages detection technology to detect and classify road damages such as potholes, cracks, and other issues in real-time. The application will be designed to be efficient and user-friendly, helping road maintenance crews to identify and repair road damages more quickly. The detection algorithm will be deployed on a Raspberry Pi and operate in real-time, with the location of each damage recorded via a GNSS module and a report generated after each detection mission.
### Target users: 
Road maintenance crews.
### Competitive product analysis: 
Visual check of field technicians who detect pavement Failure. 

## User Requirements
### User pain points:
1. Shortage of experts. Training an expert needs a lot of time and fewer people are willing to work in this field; 
2. Increasing demand for inspection. There are over 5 million kilometers of roads requiring maintenance; 
3. Lack of financial resources. Manpower and material resources cost a lot; 
4. Incorrect detection based on experience. Incorrect detection due to carelessness or incorrect criteria leading to overlooking potential damages.
### User portraits: 
Road maintenance crews’ demand of identifying and repairing road damages more quickly.
### User Scenario: 
Combined with pi, camera and GPS, the product can be equipped in a common staff car or auto guided vehicle.
### User demand list: 
1. Scan the real-time roads situation. 
2. Identify is that a pothole or a linear crack when the roads damages are detectoed. 
3. Call back GPS module in real time. 
4. Send the location information and roads damages messages.

## Product Functions
### Function list: 
#### Basic functions:
1. Real time detection;
2. Display a picture with an identification box;
3. Test results include type, confidence and size;
#### Additional functions:
1. Support traditional graphics preprocessing;
2. Display GPS coordinate;
### Priority: 
1. Real time detection;
2. Display a picture with an identification box;
3. Test results include type, confidence and size;
4. Support traditional graphics preprocessing; 
5. Display GPS coordinate;

## Data Requirements
### Data list: 
Images of pavements like alligator, crack, liner crack, potholes, etc.
### Data format: 
Live images.
### Data collection: 
Users can manually input and import data, or obtain data through existing data.

## UI/UX design
### UI design: 
A concise and beautiful interface is designed to facilitate user’s operation and use.
### UX design: 
Design easy-to-use, user friendly interactive ways to enhance the user experience.
### Design idea:
#### 1. Home Page
Blue frame on the left: Images captured by the live camera.

Grey frame on the left: Real-time Log.

Frames on the right: Type, confidence, size of the task .
#### 2. Task Page
Name of the task.

Camera: openCV parameters.

Algorithm.

Model type: Dark net, tensorflow, etc.

Model path: File path to import the algorithm.

Class path: Class to detect the path of the target (pavements like alligator, crack, liner crack, and potholes).

Weight path: File path of weight.

Algorithm parameters: Confidence, threshold, etc.

#### 3. Result Page
Information about the entire process from the beginning to the end of the detection
A list of the result.

### UI Prototype:
#### 1. Home Page

![Home](https://user-images.githubusercontent.com/108115404/231204748-cbcdf2fd-46d5-4d8f-8b46-b33bee17f577.png)

#### 2. Task Page
![Task](https://user-images.githubusercontent.com/108115404/231204936-03d969f9-13d7-4139-9b79-3a242122bccf.png)


#### 3. Result Page
![Result](https://user-images.githubusercontent.com/108115404/231204849-2280d3d0-1f2f-4859-a92f-6eb7b06522f3.png)
#### 4. Setting Page
![Setting](https://user-images.githubusercontent.com/108115404/231204916-1ae5ac57-ddc1-44cd-9f88-9267694e2207.png)



