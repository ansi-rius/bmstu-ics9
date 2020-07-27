function disablePregnantButtons() {
	document.getElementById("notPregnant").disabled = true;
	document.getElementById("pregnant").disabled = true;
	document.getElementById("feeding").disabled = true;
}

function availablePregnantButtons() {
	document.getElementById("notPregnant").disabled = false;
	document.getElementById("pregnant").disabled = false;
	document.getElementById("feeding").disabled = false;
}