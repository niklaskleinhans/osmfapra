import React, { Component } from 'react'
import { connect } from 'react-redux';

import ArrivalDisplay from '../components/ArrivalDisplay'
import Map from '../components/Map'
import Sidebar from '../components/Sidebar'

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faAngleRight } from '@fortawesome/free-solid-svg-icons'

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
        var className = '';
        if (this.props.sidebar_open){
            className += ' sidebar-open'
        }
        return(
            <div className = {className}>
                <ArrivalDisplay/>
                <Sidebar></Sidebar>
                <Map></Map>
                {!this.props.sidebar_open ?
                <div className="sidebar-trigger" > 
                    <a onClick={() => this.props.coreActions.toggleSidebar()}>
                        <FontAwesomeIcon icon={faAngleRight} size="2x"></FontAwesomeIcon>
                    </a>    
                </div> : null
                }
            </div>
        )
    }
}

const mapStateToProps = (state) => {
    return {
        name : state.core.name,
        sidebar_open : state.core.sidebar_open

    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        coreActions: bindActionCreators(coreActions, dispatch),
        mqttActions: bindActionCreators(mqttActions, dispatch)

    }
}

export default connect(mapStateToProps, mapDispatchToProps)(Home)