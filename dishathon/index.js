/* eslint-disable  func-names */
/* eslint-disable  no-console */
var channelData = require('./channelData');
var channelNowPlaying = require('./channelNowPlaying');
var troubleshoot = require('./troubleshooter');
var troubleshoot = require('./stats');

const Alexa = require('ask-sdk');

const FindChannelNumberIntent = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    return request.type === 'LaunchRequest'
      || (request.type === 'IntentRequest'
        && request.intent.name === 'FindChannelNumberIntent');
  },
  handle(handlerInput) {
    const slot = handlerInput.requestEnvelope.request.intent.slots;
    const slotChannelName=slot.channelName.resolutions.resolutionsPerAuthority[0].values[0].value.name;
    const channelArr = channelData.channelData;
    const randomFact = channelArr[slotChannelName];
    //const randomFact = slot.channelName.resolutions.resolutionsPerAuthority[0].values[0].value.name;
    const speechOutput = GET_CHANNEL_NUMBER + slotChannelName +' at '+randomFact;

    return handlerInput.responseBuilder
      .speak(speechOutput)
      .withSimpleCard(SKILL_NAME, randomFact)
      .getResponse();
  },
};

const FindPlayingNowIntent = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    return request.type === 'LaunchRequest'
      || (request.type === 'IntentRequest'
        && request.intent.name === 'FindPlayingNowIntent');
  },
  handle(handlerInput) {
    const slot = handlerInput.requestEnvelope.request.intent.slots;
    const slotChannelName=slot.channelName.resolutions.resolutionsPerAuthority[0].values[0].value.name;
    const channelArr = channelNowPlaying.channelNowPlaying;
    const randomFact = channelArr[slotChannelName];
    const speechOutput = GET_NOW_PLAYING +' at '+slotChannelName+' is '+ randomFact;

    return handlerInput.responseBuilder
      .speak(speechOutput)
      .withSimpleCard(SKILL_NAME, randomFact)
      .getResponse();
  },
};

const FindTroubleshootIntent = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    console.log("trouble");
    return request.type === 'LaunchRequest'
      || (request.type === 'IntentRequest'
        && request.intent.name === 'FindTroubleshootIntent');
  },
  handle(handlerInput) {

    const speechOutput = GET_CARD_NUMBER;

    return handlerInput.responseBuilder
      .speak(speechOutput)
      .withSimpleCard(SKILL_NAME, speechOutput)
      .getResponse();
  },
};

const FindCIDIntent = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    return request.type === 'LaunchRequest'
      || (request.type === 'IntentRequest'
        && request.intent.name === 'FindCIDIntent');
  },
  handle(handlerInput) {
    const slot = handlerInput.requestEnvelope.request.intent.slots;
    const CID=slot.CID.value;
    var speechOutput;
    troubleshoot(CID, function(result){
      speechOutput = result;
    });
    //const speechOutput = troubleshoot(CID);

    return handlerInput.responseBuilder
      .speak(speechOutput)
      .withSimpleCard(SKILL_NAME, speechOutput)
      .getResponse();
  },
};
const StatsIntent = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    return request.type === 'LaunchRequest'
      || (request.type === 'IntentRequest'
        && request.intent.name === 'StatsIntent');
  },
  handle(handlerInput) {
    const slot = handlerInput.requestEnvelope.request.intent.slots;
    const CID=slot.CID.value;
    var speechOutput;
    stats(CID, function(result){
      speechOutput = result;
    });
    //const speechOutput = troubleshoot(CID);

    return handlerInput.responseBuilder
      .speak(speechOutput)
      .withSimpleCard(SKILL_NAME, speechOutput)
      .getResponse();
  },
};
const ResetIntent = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    return request.type === 'LaunchRequest'
      || (request.type === 'IntentRequest'
        && request.intent.name === 'ResetIntent');
  },
  handle(handlerInput) {
    const speechOutput= GET_RESET_MESSAGE;
    //const speechOutput = troubleshoot(CID);

    return handlerInput.responseBuilder
      .speak(speechOutput)
      .withSimpleCard(SKILL_NAME, speechOutput)
      .getResponse();
  },
};

const HelpHandler = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    return request.type === 'IntentRequest'
      && request.intent.name === 'AMAZON.HelpIntent';
  },
  handle(handlerInput) {
    return handlerInput.responseBuilder
      .speak(HELP_MESSAGE)
      .reprompt(HELP_REPROMPT)
      .getResponse();
  },
};

const ExitHandler = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    return request.type === 'IntentRequest'
      && (request.intent.name === 'AMAZON.CancelIntent'
        || request.intent.name === 'AMAZON.StopIntent');
  },
  handle(handlerInput) {
    return handlerInput.responseBuilder
      .speak(STOP_MESSAGE)
      .getResponse();
  },
};

const SessionEndedRequestHandler = {
  canHandle(handlerInput) {
    const request = handlerInput.requestEnvelope.request;
    return request.type === 'SessionEndedRequest';
  },
  handle(handlerInput) {
    console.log(`Session ended with reason: ${handlerInput.requestEnvelope.request.reason}`);

    return handlerInput.responseBuilder.getResponse();
  },
};

const ErrorHandler = {
  canHandle() {
    return true;
  },
  handle(handlerInput, error) {
    console.log(`Error handled: ${error.message}`);

    return handlerInput.responseBuilder
      .speak('Sorry, an error occurred.')
      .reprompt('Sorry, an error occurred.')
      .getResponse();
  },
};

const SKILL_NAME = 'Dish Kale';
const GET_CHANNEL_NUMBER = 'You can find ';
const GET_NOW_PLAYING= "now playing:";
const HELP_MESSAGE = 'You can say find channel number of a channel name, or, you can say exit... What can I help you with?';
const HELP_REPROMPT = 'What can I help you with?';
const STOP_MESSAGE = 'Goodbye!';
const GET_CARD_NUMBER= ' What is your card number? ';
const GET_RESET_MESSAGE= 'You have to Hard reset your set up box. For that you have to press POWER and UP buttons in your Set up box for approximate 30 seconds.When you press these two button, the status LED will start blinking.After 30 seconds you have to turn off the power of set up box without releasing these two buttons. So you may need another buddy to help out there. And you are done. If it is still DEAD, its time to call service center.';

const scheduledata = [
  'scheduledata',
  'Another scheduledata',
  'yet another scheduledata',
]
const skillBuilder = Alexa.SkillBuilders.standard();

exports.handler = skillBuilder
  .addRequestHandlers(
    FindChannelNumberIntent,
    FindPlayingNowIntent,
    FindTroubleshootIntent,
    FindCIDIntent,
    ResetIntent,
    HelpHandler,
    ExitHandler,
    SessionEndedRequestHandler
  )
  .addErrorHandlers(ErrorHandler)
  .lambda();
