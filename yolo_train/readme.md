# yolov5 training process
## 1.set up roads damages dataset, we collect roads damages pictures from established dataset(https://github.com/titanmu/RoadCrackDetection)，online pictures, pictures taken in glasgow.
## 2.utilizing labelimg to label our pictures 
![labelimg](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/labelimg.png)
Finally, we get 6 kinds of roads damages 
|Label|	Describe|
|:--:|:--:|
|D00|Longitudinal crack|
|D10|Linear crack|
|D20|Alligator crack|
|D40|Pothole|
|D43|White cross blur|
|D30|Road rut|
## 3.Starting training
since the lack of GPU/CPU resources, I utilize Colab to train yolov5 model on my dataset.
### 3.1 Uploading my_dataset and yolov5 files to goole drive 
![labelimg](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/google_drive.png)
### 3.2 Running training code
run the code "!cd /content/drive/MyDrive/yolov5-master && python train.py --img 640 --batch 64 --epochs 30 --data /content/drive/MyDrive/yolov5-master/data/roads_damage.yaml --weights yolov5s.pt --nosave --cache"
the "roads_damage.yaml" define the training dataset and test dataset.
### 3.3 Getting training model and result
![yolov5srd](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/yolov5s_results.png)
