# yolo test
## yolov3-tiny, yolov5s, yolov5_litec compare
|model|Params|Size(M)|Map@0.5()|Map@.5:0.95|Running time on laptop(480*320 )(ms)|
|:---:|:---:|:---:|:---:|:---:|:---:|
|Yolov3-tiny|	6.06|	23.0|	33.1|	16.6|	None|
|Yolov5s|7.23M|14.0|56.0|37.2|113.23ms|
|Yolov5_litec|4.57M|9.2|50.9|32.5|59.15ms|
## label and description

|Label|	Describe|
|:--:|:--:|
|D00|Longitudinal crack|
|D10|Linear crack|
|D20|Alligator crack|
|D40|Pothole|
|D43|White cross blur|
|D30|Road rut|

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
