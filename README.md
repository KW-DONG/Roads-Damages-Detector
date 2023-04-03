# Roads Damages Detector

## Project Overview:
The Roads Damages Detector project aims to develop a mobile application that uses roads damages detection technology to detect and classify road damages such as potholes, cracks, and other issues in real-time. The application will be designed to be efficient and user-friendly, helping road maintenance crews to identify and repair road damages more quickly. The detection algorithm will be deployed on a Raspberry Pi and operate in real-time, with the location of each damage recorded via a GNSS module and a report generated after each detection mission.

## Backgrounds：
There are three types of roads damages: alligator cracks, linear cracks and pothole cracks. The repair methods and task urgency of these threes are different, it is necessary to do investigations before taking action.

<div align="left">
<img src="images/Alligator_crack.png" height=120/>
<img src="images/Linear_crack.png" height=120/>
<img src="images/pothole.png" height=120/>
</div>

## Team Organization:

|Name|ID|Role|
|---|---|---|
|Kaiwen DONG|2749039D|C++ Engineer|
|Wenjia HAO|2729835H|Software Engineer|
|Yang LIU|2749545L|UI & Marketing Designer|
|Yujie LIU|2544989lL|Engineering Assistant|
### Kaiwen DONG:
1. Designing and implementing algorithms and data structures in C++ to integrate automated road damage detection technology into the Raspberry Pi platform.
2. Developing and maintaining code libraries with a focus on code quality and readability.
3. Collaborating closely with other team members, especially software developers and quality assurance experts, to ensure smooth project progress.
4. Assisting the testing team with system testing to ensure that the detection algorithm performs accurately in various scenarios.
5.Analyzing and solving technical issues that arise during the project, working with other team members to develop and implement solutions.

Overall, the C++ engineer's role is to ensure that the C++ algorithms and data structures used in the project are accurately integrated into the Raspberry Pi platform and to collaborate with other team members to ensure the project progresses according to plan.

### Wenjia HAO:
1. Integrating the YOLOv5 model into the application and integrating it with other modules such as the image acquisition module developed by the C
2. Optimizing and debugging the YOLOv5 model to improve the accuracy and efficiency of detection.
3. Conducting model training and testing using existing datasets or generating their own datasets by collecting and labeling data.
4. Proficiency in deep learning frameworks, and strong mathematical and statistical knowledge, capable of understanding and applying the principles and mathematical models behind machine learning algorithms.
5. Collaborating with other team members such as the C++ engineer, testing engineer, and project manager to ensure smooth project progress.
6. Continuously improving and optimizing the road damage detection application to enhance the accuracy and efficiency of the detection.

In summary, the software engineer responsible would be responsible for integrating and optimizing the YOLOv5 model, conducting model training and testing, ensuring the smooth integration and collaboration of the model with the application, and continuously improving and optimizing the road damage detection application to enhance the accuracy and efficiency of detection.

### Yang LIU:
1. Develop the user interface design for the product based on the product manager's product plan and functionality requirements.
2. Continuously optimize the product interface design and user interaction process based on user research and feedback to improve user experience.
3. Work closely with the development team to ensure the product interface design can be accurately implemented.
4. Design marketing copy and creative materials, produce marketing materials and promotional videos to increase product awareness and user attraction.

### Yujie LIU:
1. Prepare the project plan, follow up the task progress according to the project plan.
2. Assist engineers with daily tasks and project management, such as scheduling meetings, taking meeting notes, and tracking task progress.
3. Collect and organize project information and technical documents to help engineers better understand project background and technical details.
4. Assist engineers in technical research and experimentation, such as writing code, running tests, and writing technical documentation.


## Process Management:
https://github.com/KW-DONG/Roads-Damages-Detector/blob/develop_qml/doc/process/Process%20Management.md

## Architecture:
<div align="left">
<img src="images/Architecture.png" height=240/>
</div>

### Hardware: 
1. Raspberry 
2. Pi Camera
3. GPS Module Receiver

### Software: 
<div align="left">
<img src="images/software.png" height=360/>
</div>

### Input: 
1. Camera video stream
2. GPS coordinates
3. Deep learning model
4. Deep learning model weights
5. Deep learning classification table
6. Image preprocessing parameters

### Output: 
During detection, real-time display of images with identified boxes is available; detection results such as type, confidence score, size, etc. can be displayed and text reports can be sent to email; logs can also be displayed.
Additional features:
1. Support for traditional image preprocessing
2. Display of maps with GPS coordinates
3. Ability to recognize other objects

Final output presentation (QT): Page design + coding


## Technical Documents:
my yolov5 training process: https://github.com/KW-DONG/Roads-Damages-Detector/tree/yolo_training/yolo_training/yolov5#readme.md

my yolov5_lite training process: https://github.com/KW-DONG/Roads-Damages-Detector/tree/yolo_training/yolo_training/YOLOv5-Lite-master#readme.md

yolo training compare and test: https://github.com/KW-DONG/Roads-Damages-Detector/blob/yolo_training/yolo_training/readme.md



## PRD (Product requirements document)
## Product Overview
### Product Name: 
Roads Damages Detector
### Product Description: 
A mobile application that uses roads damages detection technology to detect and classify road damages such as potholes, cracks, and other issues in real-time. The application will be designed to be efficient and user-friendly, helping road maintenance crews to identify and repair road damages more quickly. The detection algorithm will be deployed on a Raspberry Pi and operate in real-time, with the location of each damage recorded via a GNSS module and a report generated after each detection mission.
### Target users: 
Road maintenance crews.
Competitive product analysis: 
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
4. Send a text report to the mailbox;
5. Display Log.
#### Additional functions:
1. Support traditional graphics preprocessing;
2. Display a map with GPS coordinate;
3. Recognize other things.
### Priority: 
1. Real time detection;
2. Display a picture with an identification box;
3. Test results include type, confidence and size;
4. Send a text report to the mailbox;
5. Display Log;
6. Support traditional graphics preprocessing; 
7. Display a map with GPS coordinate;
8. Recognize other things.

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
<div align="left">
  ![Home Page](https://user-images.githubusercontent.com/108115404/229377429-d1725834-d0d0-4b4f-9cd7-acf555fc7ead.png)
</div>

#### 2. Task Page
<div align="left">
  ![Task Page](https://user-images.githubusercontent.com/108115404/229377470-8174e50b-86ab-4365-b315-3d49f2a0c21f.png)

</div>

#### 3. Result Page
