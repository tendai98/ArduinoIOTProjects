let map;
let ref;
let centerMarker;
let activeWindow;
let markers = {};
let filterArray = ["TrackerLog", "currentTrackerData"]

function createMap() {

	map = new google.maps.Map(document.getElementById("map"), {
		center: { lat:  -17.82, lng: 31.05 },
		zoom: 8,
  	});

	getTrackers();
}

function createMarkers(trackerID, info){

	if(info["currentTrackerData"]){

		let lat = info["currentTrackerData"]["lt"]
		let lon = info["currentTrackerData"]["ln"]

		console.table({lat: lat, lon: lon})

		const trackerInfo = new google.maps.InfoWindow({
			content: `<p style='font-size:16px'><b>${trackerID}</b></p>`
		});

		if(markers[trackerID]){
			markers[trackerID].setMap(null)
		}

		markers[trackerID] = new google.maps.Marker({
			position: new google.maps.LatLng(lat,lon),
			title: trackerID,
			map:map
		});

		markers[trackerID].addListener("click",()=>{

			if(!activeWindow){
				trackerInfo.open(map, markers[trackerID]);
				activeWindow = trackerInfo
			}else{
				trackerInfo.close()
				activeWindow = null
			}
		});
	}
}


function getTrackers(){

	ref = firebase.database().ref("/");

	ref.on("value",function(snapshot){
                if(snapshot.val()){
                        let obj = snapshot.val()
                        let keys = Object.keys(snapshot.val());
                        keys.forEach((key)=>{
				if(!filterArray.includes[key]){
                                	createMarkers(key, obj[key])
				}
                        });
                }
        });


	ref.on("child_added",function(snapshot){
		if(snapshot.val()){
			let obj = snapshot.val()
			let keys = Object.keys(snapshot.val());
			keys.forEach((key)=>{
				if(!filterArray.includes[key]){
					createMarkers(key, obj[key])
				}
			});
		}
	});
}

