
import React, { PropTypes } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'

import { Map as LeafletMap, TileLayer, Marker, Popup, ZoomControl} from 'react-leaflet';
import { getPosition } from 'redux-effects-geolocation';
import store from '../bootstrap';
import { throws } from 'assert';

import * as mapActions from '../services/map/actions'


class Map extends React.Component{

    constructor(props){
        super(props);
        this.state = {
            position : null
        }
    }

    invalidateMap() {
        if (this.refs.map) {
          this.refs.map.leafletElement.invalidateSize();
      }
    }

    stopGeoInterval(){
        clearInterval(this.geoInterval)
        console.log("stop interval")
    }

    componentDidMount(){
        //this.getLocation()
        this.props.mapActions.getCurrentLocation()
    }

    getLocation(){
       store.dispatch(getPosition()).then(
           Response => {
               this.setState({position : [Response.coords.latitude, Response.coords.longitude]});
               //console.log(Response)
           },
           error => {
               alert(error.message)
               console.log(error)
           }
       )
    }


    render(){
        return (
            <LeafletMap
            className='map-view'
            ref="map" 
            onDragEnd={this.invalidateMap()}
        center={[50, 10]}
        zoom={6}
        zoomControl = {false}
        attributionControl={true}
        doubleClickZoom={true}
        scrollWheelZoom={true}
        dragging={true}
        animate={true}
        easeLinearity={0.35}
      >
        <ZoomControl position="topright"/>
        <TileLayer
        attribution="&amp;copy <a href=&quot;http://osm.org/copyright&quot;>OpenStreetMap</a> contributors"
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"/>
        {this.props.position ? 
        <Marker position={this.props.position}>
          <Popup>
            Popup for any custom information.
          </Popup>
        </Marker> : null}
        {this.props.positionFriend ?
        <Marker position={this.props.positionFriend} className='friend-marker'>
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
        positionFriend : state.map.friendCoordinates,
        position : state.map.currentCoordinates

    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        mapActions: bindActionCreators(mapActions, dispatch)
    }
}

// We wrap our Sidebar with the Router, and then to the redux store
export default connect(mapStateToProps, mapDispatchToProps)(Map)