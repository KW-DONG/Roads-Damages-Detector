#  Process Management
## 1. Project process monitoring:
Ensure that the project's progress and results meet expectations and achieve project goals.
## 2. Schedule, scope, and cost management: 
Define the project scope, develop a Work Breakdown Structure (WBS), and strictly manage project change management in conjunction with project schedule and cost.
## 3. Risk management: 
Identify potential risks and focus on technical challenges by analyzing the project. Take corresponding risk response measures to minimize risks.
## 4. Quality control: 
This includes developing test plans, test cases, test reports, etc.
## 5. Communication management: 
Simple issues will be communicated through WeChat or other means, while major issues will be discussed in online or offline meetings. Difficulties that require the assistance of the professor can be addressed via email or during the weekly lab time on Wednesdays. Ensure effective communication between project team members and the professor.

|Week|Time|Meeting|Period|
|---|---|---|---|
Tuesday|10:00-12:00|Team meeting，Library Building|1.5-2h|
Wednesday|15:00-17:00|Lab meeting|2h|
## 6. Configuration management plan:

### 6.1 Branching and merging strategy：

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
  
### 6.2 Configuration library structure:
| | | |
|---|---|---|
|1|develop|
|2|develop_qml|
|3|yolo_training|
|4|main|

The initial development work would be done on the develop branch. Once QML is introduced, a new branch called develop_qml would be created for development work related to QML. Additionally, a branch called yolo_training would be used to store code and documentation related to deep learning yolo_training.
Once development work is complete on the develop_qml and yolo_training branches, the code would be merged back into the develop branch. After testing is successfully completed on the develop branch, the changes would then be merged into the main branch, which would be used to store the stable, release-ready versions of the code.
Overall, this configuration management structure allows for a clear separation of concerns between different aspects of the codebase, while still providing a clear path for integrating changes and releasing stable versions.
