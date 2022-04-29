
var firebaseConfig = {
    apiKey: "AIzaSyC3nL49UW4fwjni2Wk2UOnH2sy8xBOUQrI",
    authDomain: "esp32-firebase-80d4f.firebaseapp.com",
    databaseURL: "https://esp32-firebase-80d4f-default-rtdb.firebaseio.com",
    projectId: "esp32-firebase-80d4f",
    storageBucket: "esp32-firebase-80d4f.appspot.com",
    messagingSenderId: "976012416764",
    appId: "1:976012416764:web:00c2ca3bd96a619bc6a979",
    measurementId: "G-E4Z62SB8TZ"
 };
  // Initialize Firebase
   firebase.initializeApp(firebaseConfig);

$(document).ready(function(){
	var database = firebase.database();
	var Led1Status;
	var Led2Status;

	database.ref().on("value", function(snap){
		Led1Status = snap.val().Led1Status;
		Led2Status = snap.val().Led2Status;
	
		if(Led1Status == "1"){
			document.getElementById("unact").style.display = "none";
			document.getElementById("act").style.display = "block";
			document.getElementById("imgfan").setAttribute("src",".//Anh/electricfanon.png");
		} else {
		    document.getElementById("unact").style.display = "block";
			document.getElementById("act").style.display = "none";
			document.getElementById("imgfan").setAttribute("src",".//Anh/electricfanoff.png");
		}
		if(Led2Status == "1"){
			document.getElementById("unact1").style.display = "none";
			document.getElementById("act1").style.display = "block";
			document.getElementById("imglamp").setAttribute("src",".//Anh/lampbulbon.png");
		} else {
			document.getElementById("unact1").style.display = "block";
			document.getElementById("act1").style.display = "none";
			document.getElementById("imglamp").setAttribute("src",".//Anh/lampbulboff.png");
		}
	});

	$(".toggle-btn").click(function(){
		var firebaseRef = firebase.database().ref().child("Led1Status");
		if(Led1Status == "1"){
			firebaseRef.set("0");
			Led1Status = "0";
		} 
		else {
			firebaseRef.set("1");
			Led1Status = "1";
		}
	})
	$(".toggle-btn1").click(function(){
		var firebaseRef = firebase.database().ref().child("Led2Status");
		if(Led2Status == "1"){
			firebaseRef.set("0");
			Led2Status = "0";
		} else {
			firebaseRef.set("1");
			Led2Status = "1";
		}
	})
});

var valueTemp = firebase.database().ref('DHT11').child('Temperature');
valueTemp.on('value', snap=>{
    console.log("Nhiet do : "+snap.val());
    document.getElementById("tvTemp").innerHTML= snap.val()+"C";
});

var valueHumid = firebase.database().ref('DHT11').child('Humid');
valueHumid.on('value', snap=>{
    console.log("Do am : "+snap.val());
    document.getElementById("tvHumid").innerHTML= snap.val()+"%";
});