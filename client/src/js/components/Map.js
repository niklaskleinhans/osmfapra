
import React, { PropTypes } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'

import { Map as LeafletMap, TileLayer, Marker, Popup } from 'react-leaflet';
import { getPosition } from 'redux-effects-geolocation';
import store from '../bootstrap';
import { throws } from 'assert';

class Map extends React.Component{

    constructor(props){
        super(props);
        this.state = {
            position : null
        }
    }

    startGeoInterval(){
        console.log("start interval")
        this.geoInterval = setInterval(()=> {
            this.getLocation({ enableHighAccuracy : true})
            }, 1000)
    }

    stopGeoInterval(){
        clearInterval(this.geoInterval)
        console.log("stop interval")
    }

    componentDidMount(){
        this.startGeoInterval()
    }

    getLocation(){
       store.dispatch(getPosition()).then(
           Response => {
               this.setState({position : [Response.coords.latitude, Response.coords.longitude]});
               //console.log(Response)
           },
           error => {
               alert(error.message)
               clearInterval(this.geoInterval)
               console.log(error)
           }
       )
    }


    render(){
        return (
            <LeafletMap
        center={[50, 10]}
        zoom={6}
        attributionControl={true}
        zoomControl={true}
        doubleClickZoom={true}
        scrollWheelZoom={true}
        dragging={true}
        animate={true}
        easeLinearity={0.35}
      >
        <TileLayer
        attribution="&amp;copy <a href=&quot;http://osm.org/copyright&quot;>OpenStreetMap</a> contributors"
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"/>
        {this.state.position ? 
        <Marker position={this.state.position}>
          <Popup>
            Popup for any custom information.
          </Popup>
        </Marker> : null}
      </LeafletMap>
    );
    }
}


/**
 * Export our component
 *
 * We also integrate our global store, using connect()
 **/

const mapStateToProps = (state, ownProps) => {
    return {

    }
}

const mapDispatchToProps = (dispatch) => {
    return {
    }
}

// We wrap our Sidebar with the Router, and then to the redux store
export default connect(mapStateToProps, mapDispatchToProps)(Map)