# yolo test
## yolov3-tiny, yolov5s, yolov5_litec compare
|model|Params|Size(M)|Map@0.5()|Map@.5:0.95|Running time on laptop(480*320 )(ms)|
|:---:|:---:|:---:|:---:|:---:|:---:|
|Yolov3-tiny|	6.06|	23.0|	33.1|	16.6|	None|
|Yolov5s|7.23M|14.0|56.0|37.2|113.23ms|
|Yolov5_litec|4.57M|9.2|50.9|32.5|59.15ms|
## model results details compare
### yolov5s training details 
![yolov5srd](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/yolov5lite_result.png)
### yolov5_lite training details
![yolov5_literd](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/yolov5lite_result.png)
We can see that with the epoch increase, loss decrease and precision increase in yolov5s model and yolov5_lite model. As for -mAP@0.5, these two model can reach 0.6 while as for mAP@0.5:0.95, yolov5s a little higher than yolov5_lite. Considering the -running time and accuracy, we finally use yolov5_lite which is quicker and the accuracy is also high.
## label and description

|Label|	Describe|
|:--:|:--:|
|D00|Longitudinal crack|
|D10|Linear crack|
|D20|Alligator crack|
|D40|Pothole|
|D43|White cross blur|
|D30|Road rut|

## yolov5_litec resultes analysis

![yolov5lite_confusionmatrix](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/yolov5lite_confusion_matrix.png)
As shown the confusionmatrix of yolov5lite_c model, we can find that D00 D40 may be confused with background maybe there are less pictures added. D10 are more likely to be detected while D30 is more difficult to be detected.
## images test utilizing yolov5_litec(ncnn)

|File_name|size|Label&confidence|Laptop_time|RaspberryPi1_time|
|:---:|:---:|:---:|:---:|:---:|
|001.jpg|480*320|D10 59.5%|51.19 ms|160.35ms|
|pothole_023.jpg|225*300|D40 73.6%|35.63ms|273.42ms|
|101.jpg|480*320|D20 49.9%|67.11 ms|392.87ms|
|148.jpg|600*600|D43 87.6%|66.82ms|280ms|
|pothole_085.jpg|274*184|D40 66.4%|35.63ms|273.42ms|
|rut_042.jpg|275*183|D30 71.2%|39.38ms|270.89ms|
|white_038.jpg|600*600|D43 67.2%|45.91ms|306.48ms|
|Zidane.jpg|1280*720|None|36.99ms|116.58ms|

## images and results show
### 001.jpg show
![fig001](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/fig001.png)
### 101.jpg show
![fig101](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/fig101.png)
### 148.jpg show
![fig148](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/fig148.png)
### pothole_023.jpg show
![figpot023](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/figpot023.png)
### pothole_085.jpg show
![figpot085](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/figpot083.png)
### rut_042.jpg show
![figrut042](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/figrut042.png)
### white_038.jpg show
![figwhite0438](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/figwhite038.png)
### zidane.jpg show
![figzidane](https://raw.githubusercontent.com/KW-DONG/Roads-Damages-Detector/yolo_training/yolo_training/pictures/figzidane.png)
