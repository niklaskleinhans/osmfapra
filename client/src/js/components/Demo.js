import React from 'react';
import {geolocated} from 'react-geolocated';
 
class Demo extends React.Component {
  render() {
    return (null) 
}
}
 
export default geolocated({
  positionOptions: {
    enableHighAccuracy: false,
  },
  userDecisionTimeout: 5000,
})(Demo);