import React, { Component } from 'react'
import { connect } from 'react-redux';
import { getPosition } from 'redux-effects-geolocation';

import store from '../bootstrap'

import * as mqttActions from '../services/mqtt/actions'
import * as mapActions from '../services/map/actions'
import Notifications from '../components/Notifications'

import { bindActionCreators } from 'redux';

class ShareLocation extends Component{
    constructor(props){
        super(props)
    }

    componentDidMount(){
        this.props.mqttActions.initMqttConnection({})
        this.startGeoInterval()
        //this.startSendingLocation()
    }

    startSendingLocation(){
        console.log("start sending location")
        this.locationInterval = setInterval(()=> {
            this.props.mapActions.sendLocation()
        }, 1000)
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

    getLocation(){
        getPosition( position => {
            console.log(position)
        })
       store.dispatch(getPosition()).then(
           Response => {
               console.log({position : [Response.coords.latitude, Response.coords.longitude]});
               store.dispatch(mqttActions.mqttPublish('client/coordinates/'+ this.props.match.params.sharekey, JSON.stringify({position : [Response.coords.latitude, Response.coords.longitude]})))
               //this.props.mqttActions.publish('client/coordinates', {position : [Response.coords.latitude, Response.coords.longitude]})
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
        return(
            <div>
                <h1>You are sharing now your location</h1>
                <Notifications/>
            </div>
        )
    }
}

const mapStateToProps = (state) => {
    return {
    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        mqttActions: bindActionCreators(mqttActions, dispatch),
        mapActions: bindActionCreators(mapActions, dispatch),

    }
}

export default connect(mapStateToProps, mapDispatchToProps)(ShareLocation)