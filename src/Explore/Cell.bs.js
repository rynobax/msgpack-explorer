// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Util$ReactTemplate = require("../Util.bs.js");
var MPString$ReactTemplate = require("./Cells/MPString.bs.js");

var component = ReasonReact.statelessComponent("Cell");

function make(data, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              var parseHex = function (_$staropt$star, _hex) {
                while(true) {
                  var hex = _hex;
                  var $staropt$star = _$staropt$star;
                  var res = $staropt$star !== undefined ? $staropt$star : /* [] */0;
                  if (hex) {
                    var a = hex[0];
                    if (a >= 160 && a <= 191) {
                      var match = Util$ReactTemplate.splitAt(hex[1], 5);
                      _hex = match[1];
                      _$staropt$star = /* :: */[
                        ReasonReact.element(undefined, undefined, MPString$ReactTemplate.make($$Array.of_list(match[0]), /* array */[])),
                        res
                      ];
                      continue ;
                    } else {
                      return res;
                    }
                  } else {
                    return res;
                  }
                };
              };
              var cells = $$Array.of_list(parseHex(undefined, data));
              return React.createElement("div", undefined, cells);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */
