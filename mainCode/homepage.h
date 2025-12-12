// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en" > 
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">

<title> Anxiety Detector Website </title>

<style>
   
   body {       
	background-color: rgb(88, 196, 187);
	}
	.flex-Container{
        display: flex;
        flex-direction: column;
        background-color: rgb(88, 196, 187);
        align-items: center;
      }
    h1{
    font: bold;
    font-size: 40px;
    font-family: Arial;
    color: navy;
	text-align: center;
  }
  p{
    font-size: 25px;
    font-family: Arial;
    color: navy;
	text-align: center;
   }  
  th, td {
    background-color: rgb(102, 221, 175);
    font-size: 25px;
    padding: 10px;
    text-align: left;
    border: 2px solid #383838;
}
</style>
</head>
	<body>
		<div class="flex-Container">
		<h1> Sensor Readings </h1>
      
		<p>Refresh page to get latest readings</p>
    
		<table>
        <tr>
          <th>Sensor</th>
          <th>Value</th>
          
        </tr>
        <tr>
          <td>Temperature</td>
          <td> )=====");
String homePagePart2 = F(R"=====(</td>
          
        </tr>
        <tr>
          <td>Light</td>
          <td> )=====");
String homePagePart3 = F(R"=====(</td> 
          <!-- Very Dark, Dark, Ambient, Bright, Very Bright-->
        </tr>
        <tr>
          <td>HeartRate</td>
          <td>)=====");
String homePagePart4 = F(R"=====( bpm</td>
        </tr>
      </table>
     </div>
	</body>
</html>)=====");