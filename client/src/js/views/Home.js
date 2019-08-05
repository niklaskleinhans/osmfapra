import React, { Component } from 'react'
import { connect } from 'react-redux';

import Map from '../components/Map'
import Sidebar from '../components/Sidebar'

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
                <Sidebar></Sidebar>
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