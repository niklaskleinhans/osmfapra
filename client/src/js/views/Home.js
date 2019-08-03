import React, { Component } from 'react'
import { connect } from 'react-redux';

import Map from '../components/Map'
import Demo from '../components/Demo'

import * as coreActions from '../services/core/actions'
import * as mqttActions from '../services/mqtt/actions'
import { bindActionCreators } from 'redux';
class Home extends Component{
    constructor(props){
        super(props)
    }


    setName(){
        this.props.coreActions.setName("Niklas")
    }

    createNotification(){
        this.props.coreActions.createNotification({content: "what a shit", type: 'good'})
        this.props.mqttActions.mqttPublish('test', 'test')
    }

    render(){
        return(
            <div>
                <h1>Home sweet Home</h1>
                <h2>{this.props.name}</h2>
                <button onClick={e => this.createNotification()}>click me </button>
                <Map></Map>
            </div>
        )
    }
}

const mapStateToProps = (state) => {
    return {
        name : state.core.name

    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        coreActions: bindActionCreators(coreActions, dispatch),
        mqttActions: bindActionCreators(mqttActions, dispatch)

    }
}

export default connect(mapStateToProps, mapDispatchToProps)(Home)