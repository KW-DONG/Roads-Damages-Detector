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

1. Project process monitoring: Ensure that the project's progress and results meet expectations and achieve project goals.
2. Schedule, scope, and cost management: Define the project scope, develop a Work Breakdown Structure (WBS), and strictly manage project change management in conjunction with project schedule and cost.
3. Risk management: Identify potential risks and focus on technical challenges by analyzing the project. Take corresponding risk response measures to minimize risks.
4. Quality control: This includes developing test plans, test cases, test reports, etc.
5. Communication management: Simple issues will be communicated through WeChat or other means, while major issues will be discussed in online or offline meetings. Difficulties that require the assistance of the professor can be addressed via email or during the weekly lab time on Wednesdays. Ensure effective communication between project team members and the professor.

|Week|Time|Meeting|Period|
|---|---|---|---|
Tuesday|10:00-12:00|Team meeting，Library Building|1.5-2h|
Wednesday|15:00-17:00|Lab meeting|2h|
6. Configuration management plan

6.1 Branching and merging strategy：

  --6.1.1 Keep the main branch stable：
  The main branch is typically the most important branch in the codebase and should be kept stable. This means only well-tested code should be merged into the main branch. All development work should be done in other branches.
  
  --6.1.2 Use a development branch for work：
  To prevent any issues on the main branch, create a development branch to do all work. This branch should be created from the main branch and code should be merged back into the main branch once the development work is complete.
  
  --6.1.3 Use feature branches for functionality development：
  When adding new functionality, create a feature branch from the development branch. Do the development work on the feature branch, ensuring the code is testable and stable, then merge the feature branch back into the development branch.
  
  --6.1.4 Conduct code reviews regularly：
  Conduct regular code reviews to ensure all code meets the codebase's standards. The review process should be done on the feature branches, not the main branch.
  
  --6.1.5 Keep branches clean：
  Once a feature branch has completed its work and has been merged back into the development branch, it should be deleted. This keeps the branches clean and avoids confusion or mistaken merges.
  
6.2 Configuration library structure
| | | |
|---|---|---|
|1|develop|
|2|develop_qml|
|3|yolo_training|
|4|main|

The initial development work would be done on the develop branch. Once QML is introduced, a new branch called develop_qml would be created for development work related to QML. Additionally, a branch called yolo_training would be used to store code and documentation related to deep learning yolo_training.
Once development work is complete on the develop_qml and yolo_training branches, the code would be merged back into the develop branch. After testing is successfully completed on the develop branch, the changes would then be merged into the main branch, which would be used to store the stable, release-ready versions of the code.
Overall, this configuration management structure allows for a clear separation of concerns between different aspects of the codebase, while still providing a clear path for integrating changes and releasing stable versions.

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
