var storage = (function() {
	var uid = new Date();
	var storage;
	var result;
	try {
		(storage = window.localStorage).setItem(uid, uid);
		result = storage.getItem(uid) === uid;
		storage.removeItem(uid);
		return result && storage;
	} catch (exception) {}
}());

export let getStorage = function(key, default_value = {}){
	if (storage){
		var value = storage.getItem(key);
		if (value){
			return JSON.parse(value);
		} else {
			return default_value;
		}

	} else {
		console.warn("localStorage not available. Using default value for '"+key+"'.");
		return default_value;
	}
}
export let setStorage = function(key, value, replace = false){
	if (storage){
        var new_value;
		var stored_value = storage.getItem(key);

		// We have nothing to merge with, or we want to completely replace previous value
		if (!stored_value || replace){
			new_value = value;

		// Merge new value with existing
		} else {
			new_value = Object.assign(
				{},
				JSON.parse(stored_value),
				value
			);
		}
		storage.setItem(key, JSON.stringify(new_value));
		return;
	} else {
		console.warn("localStorage not available. '"+key+"'' will not perist when you close your browser.");
		return;
	}
}

export function pointDistance(x,y){
	var R = 6371e3; // metres
	var φ1 = x[0] * Math.PI/180
	var φ2 = y[0] * Math.PI/180
	var Δφ = (y[0]-x[0]) * Math.PI/180
	var Δλ = (y[1]-x[1]) * Math.PI/180

	var a = Math.sin(Δφ/2) * Math.sin(Δφ/2) +
        Math.cos(φ1) * Math.cos(φ2) *
        Math.sin(Δλ/2) * Math.sin(Δλ/2);
	var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));

	var d = R * c;
	return d
}

export function getPositionByEpsilonDistance(point, pointlist, e){
	var currentShortestDistance = e+1;
	var pointOfList =0; 
	pointlist.forEach(i =>{
		var nodeOfPath = [Number.parseFloat(i[0].replace(',','.').replace(' ','')), Number.parseFloat(i[1].replace(',','.').replace(' ',''))]
		if (pointDistance(point, nodeOfPath) < currentShortestDistance ){
			currentShortestDistance = pointDistance(point, nodeOfPath)
			pointOfList = nodeOfPath
		}
	})
	//console.log(currentShortestDistance)
	if (currentShortestDistance < e){
		return pointOfList
	}else{
		return point
	}
}