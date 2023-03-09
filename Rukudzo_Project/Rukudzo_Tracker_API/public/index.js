let map;
let ref;
let centerMarker;
let activeWindow;


function createMap() {

	map = new google.maps.Map(document.getElementById("map"), {
		center: { lat:  -17.824858, lng: 31.053028 },
		zoom: 8,
  	});

	getTrackers();
}

function createMarkers(trackerID, info){

	let lat = info.currentLocation["lat"]
	let lon = info.currentLocation["lon"]

	console.log(lat,lon)
	const trackerInfo = new google.maps.InfoWindow({
		content: `<p style='font-size:16px'> <b>Tracker ID: </b>${trackerID}</p>`
	});

	let marker = new google.maps.Marker({
		position: new google.maps.LatLng(lat,lon),
		title: trackerID,
		map:map
	});

	marker.addListener("click",()=>{

		if(!activeWindow){
			trackerInfo.open(map,marker);
			activeWindow = trackerInfo
		}else{
			trackerInfo.close()
			activeWindow = null
		}
	});
}


function getTrackers(){

	ref = firebase.database().ref("/");

	ref.on("value",function(snapshot){
                if(snapshot.val()){
                        let obj = snapshot.val()
                        let keys = Object.keys(snapshot.val());
                        keys.forEach((key)=>{
                                delete obj[key].tracking
                                createMarkers(key, obj[key])
                        });
                }
        });


	ref.on("child_added",function(snapshot){
		if(snapshot.val()){
			let obj = snapshot.val()
			let keys = Object.keys(snapshot.val());
			keys.forEach((key)=>{
				delete obj[key].tracking
				createMarkers(key, obj[key])
			});
		}
	});
}

