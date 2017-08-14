import React, { Component } from 'react';
import PropTypes from 'prop-types';
import Input from '../../common/Input/Input';
import DataManager from '../../../api/DataManager';

class Property extends Component {
  constructor(props) {
    super(props);

    this.state = { value: props.Value };

    this.onChange = this.onChange.bind(this);
    this.updateValue = this.updateValue.bind(this);
  }

  componentDidMount() {
    DataManager.subscribe(this.uri, this.updateValue);
  }

  componentWillUnmount() {
    DataManager.unsubscribe(this.uri, this.updateValue);
  }

  onChange(event) {
    const { value } = event.currentTarget;

    this.saveValue(value);

    // optimistic UI change!
    this.setState({ value });
  }

  get uri() {
    const { Identifier } = this.props.Description;
    return Identifier;
  }

  get inputType() {
    const { Description } = this.props;
    switch (Description.Type) {
      case 'StringProperty':
      default:
        return Input;
    }
  }

  /**
   * Send value to OpenSpace
   */
  saveValue(value) {
    DataManager.setValue(this.uri, value);
  }

  /**
   * New value received from OpenSpace
   * @param Value - the value
   */
  updateValue({ Value }) {
    this.setState({ value: Value });
  }

  render() {
    const { Description } = this.props;
    const { value } = this.state;
    const PropInput = this.inputType;
    return (
      <PropInput value={value} placeholder={Description.Name} onChange={this.onChange} />
    );
  }
}

Property.propTypes = {
  Description: PropTypes.object,
  Value: PropTypes.oneOfType([PropTypes.string, PropTypes.number]).isRequired,
};


export default Property;
