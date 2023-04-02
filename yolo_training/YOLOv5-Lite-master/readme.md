# Why utilize yolov5_lite
1.Speed up.
2.Accuracy almost same.
|ID|	Model	|Input_size	|Flops|	Params|	Size（M）|	Map@0.5	|Map@.5:0.95|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|001|	yolo-fastest|	320×320	|0.25G|	0.35M|	1.4	|24.4	|-|
|002|	YOLOv5-Liteeours|	320×320|	0.73G|	0.78M	|1.7|	35.1|	-|
|003|	NanoDet-m	|320×320|	0.72G|	0.95M|	1.8	|-|	20.6|
|004|	yolo-fastest-xl|	320×320|	0.72G|	0.92M|	3.5|	34.3|	-|
|005|	YOLOXNano|	416×416|	1.08G|	0.91M|	7.3(fp32)|	-	|25.8|
|006|	yolov3-tiny|	416×416|	6.96G|	6.06M|	23.0	|33.1	|16.6|
|007|	yolov4-tiny|	416×416|	5.62G|	8.86M|	33.7	|40.2	|21.7|
|008|	YOLOv5-Litesours|	416×416|	1.66G|	1.64M|	3.4	|42.0	|25.2|
|009|	YOLOv5-Litecours|	512×512|	5.92G|	4.57M|	9.2	|50.9	|32.5|
|010|	NanoDet-EfficientLite2|	512×512|	7.12G|	4.71M|	18.3	|-	|32.6|
|011|	YOLOv5s(6.0)|	640×640|	16.5G|	7.23M|	14.0	|56.0	|37.2|
|012|	YOLOv5-Litegours|	640×640|	15.6G|	5.39M|	10.9|	57.6	|39.1|
# yolov5_lite training process
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
since the lack of GPU/CPU resources, I utilize Colab to train yolov5_lite model on my dataset.
### 3.1 Uploading my_dataset and yolov5_lite files to goole drive 
![labelimg](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/google_drive.png)
### 3.2 Running training code
run the code  
  `!cd /content/drive/MyDrive/YOLOv5-Lite-master_full && python train.py --data '/content/drive/MyDrive/YOLOv5-Lite-master_full/data/roads_damage.yaml' --cfg '/content/drive/MyDrive/YOLOv5-Lite-master_full/models/v5Lite-s.yaml' --weights '/content/drive/MyDrive/YOLOv5-Lite-master_full/models/v5lite-s.pt' --epoch 300 --batch-size 32 --adam`  
the "roads_damage.yaml" define the training dataset and test dataset.
### 3.3 Getting training model and result
![yolov5_literd](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/yolov5lite_result.png)
![yolov5lite_confusionmatrix](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/yolov5lite_confusion_matrix.png)
As shown the confusionmatrix of yolov5lite_c model, we can find that D00 D40 may be confused with background maybe there are less pictures added. D10 are more likely to be detected while D30 is more difficult to be detected.
### 3.4 Transferming .pt file to .onnx file for NCNN framework prepare
run the code  
`!cd /content/drive/MyDrive/YOLOv5-Lite-master_full && python -m onnxsim /content/drive/MyDrive/YOLOv5-Lite-master_full/runs/train/exp3/weights/best.onnx /content/drive/MyDrive/YOLOv5-Lite-master_full/runs/train/exp3/weights/best-sim.onnx`  Finally, we 
can get best.onnx file.
