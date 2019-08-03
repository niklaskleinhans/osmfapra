import React, { Component } from 'react';
import { bindActionCreators} from 'redux'
import { connect } from 'react-redux'

import Home from './views/Home'
import Notifications from './components/Notifications'

import * as mqttActions from './services/mqtt/actions'

class App extends Component {

  constructor(props){
    super(props)
  }

  componentDidMount(){
    this.props.mqttActions.initMqttConnection()
  }


  render() {
    var className = "App";
    return (
      <div className={className}>
        <div className="body">
          <Home/>
          <Notifications/>
        </div>
      </div>
    );
  }
}

const mapStateToProps = (state, ownProps) => {
  return{}
}

const mapDispatchToProps = (dispatch) => {
  return {
    mqttActions: bindActionCreators(mqttActions, dispatch)
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(App);