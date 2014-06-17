(function() {

    var layouts = {
        en_US: { name: "US Standard",
            keys: [
                [["`", "~"], ["1", "!"], ["2", "@"], ["3", "#"], ["4", "$"], ["5", "%"], ["6", "^"], ["7", "&"], ["8", "*"], ["9", "("], ["0", ")"], ["-", "_"], ["=", "+"], ["Bksp", "Bksp"]],
                [["Tab", "Tab"], ["q", "Q"], ["w", "W"], ["e", "E"], ["r", "R"], ["t", "T"], ["y", "Y"], ["u", "U"], ["i", "I"], ["o", "O"], ["p", "P"], ["[", "{"], ["]", "}"], ["\\", "|"]],
                [["Caps", "Caps"], ["a", "A"], ["s", "S"], ["d", "D"], ["f", "F"], ["g", "G"], ["h", "H"], ["j", "J"], ["k", "K"], ["l", "L"], [";", ":"], ["'", '"'], ["Enter", "Enter"]],
                [["Shift", "Shift"], ["z", "Z"], ["x", "X"], ["c", "C"], ["v", "V"], ["b", "B"], ["n", "N"], ["m", "M"], [",", "<"], [".", ">"], ["/", "?"], ["Shift", "Shift"]],
                [[" ", " "]]
            ]
        },
        en_GB: { name: "United Kingdom",
            keys: [
                [["`", "\u00ac", "\u00a6"], ["1", "!"], ["2", '"'], ["3", "\u00a3"], ["4", "$", "\u20ac"], ["5", "%"], ["6", "^"], ["7", "&"], ["8", "*"], ["9", "("], ["0", ")"], ["-", "_"], ["=", "+"], ["Bksp", "Bksp"]],
                [["Tab", "Tab"], ["q", "Q"], ["w", "W"], ["e", "E", "\u00e9", "\u00c9"], ["r", "R"], ["t", "T"], ["y", "Y"], ["u", "U", "\u00fa", "\u00da"], ["i", "I", "\u00ed", "\u00cd"], ["o", "O", "\u00f3", "\u00d3"], ["p", "P"], ["[", "{"], ["]", "}"], ["#", "~"]],
                [["Caps", "Caps"], ["a", "A", "\u00e1", "\u00c1"], ["s", "S"], ["d", "D"], ["f", "F"], ["g", "G"], ["h", "H"], ["j", "J"], ["k", "K"], ["l", "L"], [";", ":"], ["'", "@"], ["Enter", "Enter"]],
                [["Shift", "Shift"], ["\\", "|"], ["z", "Z"], ["x", "X"], ["c", "C"], ["v", "V"], ["b", "B"], ["n", "N"], ["m", "M"], [",", "<"], [".", ">"], ["/", "?"], ["Shift", "Shift"]],
                [[" ", " ", " ", " "], ["AltGr", "AltGr"]]
            ]
        },
        fr_FR: { name: "Fran\u00e7ais",
            keys: [
                [["\u00b2", "\u00b3"], ["&", "1"], ["\u00e9", "2", "~"], ['"', "3", "#"], ["'", "4", "{"], ["(", "5", "["], ["-", "6", "|"], ["\u00e8", "7", "`"], ["_", "8", "\\"], ["\u00e7", "9", "^"], ["\u00e0", "0", "@"], [")", "\u00b0", "]"], ["=", "+", "}"], ["Bksp", "Bksp"]],
                [["Tab", "Tab"], ["a", "A"], ["z", "Z"], ["e", "E", "\u20ac"], ["r", "R"], ["t", "T"], ["y", "Y"], ["u", "U"], ["i", "I"], ["o", "O"], ["p", "P"], ["^", "\u00a8"], ["$", "\u00a3", "\u00a4"], ["*", "\u03bc"]],
                [["Caps", "Caps"], ["q", "Q"], ["s", "S"], ["d", "D"], ["f", "F"], ["g", "G"], ["h", "H"], ["j", "J"], ["k", "K"], ["l", "L"], ["m", "M"], ["\u00f9", "%"], ["Enter", "Enter"]],
                [["Shift", "Shift"], ["<", ">"], ["w", "W"], ["x", "X"], ["c", "C"], ["v", "V"], ["b", "B"], ["n", "N"], [",", "?"], [";", "."], [":", "/"], ["!", "\u00a7"], ["Shift", "Shift"]],
                [[" ", " ", " ", " "], ["AltGr", "AltGr"]]
            ]
        },
        de_DE: { name: "Deutsch",
            keys: [
                [["^", "\u00b0"], ["1", "!"], ["2", '"', "\u00b2"], ["3", "\u00a7", "\u00b3"], ["4", "$"], ["5", "%"], ["6", "&"], ["7", "/", "{"], ["8", "(", "["], ["9", ")", "]"], ["0", "=", "}"], ["\u00df", "?", "\\"], ["\u00b4", "`"], ["Bksp", "Bksp"]],
                [["Tab", "Tab"], ["q", "Q", "@"], ["w", "W"], ["e", "E", "\u20ac"], ["r", "R"], ["t", "T"], ["z", "Z"], ["u", "U"], ["i", "I"], ["o", "O"], ["p", "P"], ["\u00fc", "\u00dc"], ["+", "*", "~"], ["#", "'"]],
                [["Caps", "Caps"], ["a", "A"], ["s", "S"], ["d", "D"], ["f", "F"], ["g", "G"], ["h", "H"], ["j", "J"], ["k", "K"], ["l", "L"], ["\u00f6", "\u00d6"], ["\u00e4", "\u00c4"], ["Enter", "Enter"]],
                [["Shift", "Shift"], ["<", ">", "\u00a6"], ["y", "Y"], ["x", "X"], ["c", "C"], ["v", "V"], ["b", "B"], ["n", "N"], ["m", "M", "\u00b5"], [",", ";"], [".", ":"], ["-", "_"], ["Shift", "Shift"]],
                [[" ", " ", " ", " "], ["AltGr", "AltGr"]]
            ]
        },
        it_IT: { name: "Italiano",
            keys: [
                [["\\", "|"], ["1", "!"], ["2", '"'], ["3", "\u00a3"], ["4", "$", "\u20ac"], ["5", "%"], ["6", "&"], ["7", "/"], ["8", "("], ["9", ")"], ["0", "="], ["'", "?"], ["\u00ec", "^"], ["Bksp", "Bksp"]],
                [["Tab", "Tab"], ["q", "Q"], ["w", "W"], ["e", "E", "\u20ac"], ["r", "R"], ["t", "T"], ["y", "Y"], ["u", "U"], ["i", "I"], ["o", "O"], ["p", "P"], ["\u00e8", "\u00e9", "[", "{"], ["+", "*", "]", "}"], ["\u00f9", "\u00a7"]],
                [["Caps", "Caps"], ["a", "A"], ["s", "S"], ["d", "D"], ["f", "F"], ["g", "G"], ["h", "H"], ["j", "J"], ["k", "K"], ["l", "L"], ["\u00f2", "\u00e7", "@"], ["\u00e0", "\u00b0", "#"], ["Enter", "Enter"]],
                [["Shift", "Shift"], ["<", ">"], ["z", "Z"], ["x", "X"], ["c", "C"], ["v", "V"], ["b", "B"], ["n", "N"], ["m", "M"], [",", ";"], [".", ":"], ["-", "_"], ["Shift", "Shift"]],
                [[" ", " ", " ", " "], ["AltGr", "AltGr"]]
            ]
        },
        es_ES: { name: "Espa\u00f1ol",
            keys: [
                [["\u00ba", "\u00aa", "\\"], ["1", "!", "|"], ["2", '"', "@"], ["3", "'", "#"], ["4", "$", "~"], ["5", "%", "\u20ac"], ["6", "&", "\u00ac"], ["7", "/"], ["8", "("], ["9", ")"], ["0", "="], ["'", "?"], ["\u00a1", "\u00bf"], ["Bksp", "Bksp"]],
                [["Tab", "Tab"], ["q", "Q"], ["w", "W"], ["e", "E"], ["r", "R"], ["t", "T"], ["y", "Y"], ["u", "U"], ["i", "I"], ["o", "O"], ["p", "P"], ["`", "^", "["], ["+", "*", "]"], ["\u00e7", "\u00c7", "}"]],
                [["Caps", "Caps"], ["a", "A"], ["s", "S"], ["d", "D"], ["f", "F"], ["g", "G"], ["h", "H"], ["j", "J"], ["k", "K"], ["l", "L"], ["\u00f1", "\u00d1"], ["\u00b4", "\u00a8", "{"], ["Enter", "Enter"]],
                [["Shift", "Shift"], ["<", ">"], ["z", "Z"], ["x", "X"], ["c", "C"], ["v", "V"], ["b", "B"], ["n", "N"], ["m", "M"], [",", ";"], [".", ":"], ["-", "_"], ["Shift", "Shift"]],
                [[" ", " ", " ", " "], ["AltGr", "AltGr"]]
            ]
        },
        ja_JP: { name: "\u65e5\u672c\u8a9e",
            keys: [
                [["\uff5e"], ["\u306c", "\u30cc"], ["\u3075", '\u30d5'], ["\u3042", "\u30a2", "\u3041", "\u30a1"], ["\u3046", "\u30a6", "\u3045", "\u30a5"], ["\u3048", "\u30a8", "\u3047", "\u30a7"], ["\u304a", "\u30aa", "\u3049", "\u30a9"], ["\u3084", "\u30e4", "\u3083", "\u30e3"], ["\u3086", "\u30e6", "\u3085", "\u30e5"], ["\u3088", "\u30e8", "\u3087", "\u30e7"], ["\u308f", "\u30ef", "\u3092", "\u30f2"], ["\u307b", "\u30db", "\u30fc", "\uff1d"], ["\u3078", "\u30d8" , "\uff3e", "\uff5e"], ["Bksp", "Bksp"]],
                [["Tab", "Tab"], ["\u305f", "\u30bf"], ["\u3066", "\u30c6"], ["\u3044", "\u30a4", "\u3043", "\u30a3"], ["\u3059", "\u30b9"], ["\u304b", "\u30ab"], ["\u3093", "\u30f3"], ["\u306a", "\u30ca"], ["\u306b", "\u30cb"], ["\u3089", "\u30e9"], ["\u305b", "\u30bb"], ["\u3001", "\u3001", "\uff20", "\u2018"], ["\u3002", "\u3002", "\u300c", "\uff5b"], ["\uffe5", "", "", "\uff0a"], ['\u309B', '"', "\uffe5", "\uff5c"]],
                [["Caps", "Caps"], ["\u3061", "\u30c1"], ["\u3068", "\u30c8"], ["\u3057", "\u30b7"], ["\u306f", "\u30cf"], ["\u304d", "\u30ad"], ["\u304f", "\u30af"], ["\u307e", "\u30de"], ["\u306e", "\u30ce"], ["\u308c", "\u30ec", "\uff1b", "\uff0b"], ["\u3051", "\u30b1", "\uff1a", "\u30f6"], ["\u3080", "\u30e0", "\u300d", "\uff5d"], ["Enter", "Enter"]],
                [["Shift", "Shift"], ["\u3064", "\u30c4"], ["\u3055", "\u30b5"], ["\u305d", "\u30bd"], ["\u3072", "\u30d2"], ["\u3053", "\u30b3"], ["\u307f", "\u30df"], ["\u3082", "\u30e2"], ["\u306d", "\u30cd", "\u3001", "\uff1c"], ["\u308b", "\u30eb", "\u3002", "\uff1e"], ["\u3081", "\u30e1", "\u30fb", "\uff1f"], ["\u308d", "\u30ed", "", "\uff3f"], ["Shift", "Shift"]],
                [["AltLk", "AltLk"], [" ", " ", " ", " "], ["Alt", "Alt"]]
            ]
        },
        zh_CN: { name: "\u4e2d\u6587\u4ed3\u9889\u8f93\u5165\u6cd5",
            keys: [
                [["\u20AC", "~"], ["1", "!"], ["2", "@"], ["3", "#"], ["4", "$"], ["5", "%"], ["6", "^"], ["7", "&"], ["8", "*"], ["9", ")"], ["0", "("], ["-", "_"], ["=", "+"], ["Bksp", "Bksp"]],
                [["Tab", "Tab"], ["\u624B", "q"], ["\u7530", "w"], ["\u6C34", "e"], ["\u53E3", "r"], ["\u5EFF", "t"], ["\u535C", "y"], ["\u5C71", "u"], ["\u6208", "i"], ["\u4EBA", "o"], ["\u5FC3", "p"], ["[", "{"], ["]", "}"], ["\\", "|"]],
                [["Caps", "Caps"], ["\u65E5", "a"], ["\u5C38", "s"], ["\u6728", "d"], ["\u706B", "f"], ["\u571F", "g"], ["\u7AF9", "h"], ["\u5341", "j"], ["\u5927", "k"], ["\u4E2D", "l"], [";", ":"], ["'", '"'], ["Enter", "Enter"]],
                [["Shift", "Shift"], ["\uFF3A", "z"], ["\u96E3", "x"], ["\u91D1", "c"], ["\u5973", "v"], ["\u6708", "b"], ["\u5F13", "n"], ["\u4E00", "m"], [",", "<"], [".", ">"], ["/", "?"], ["Shift", "Shift"]],
                [[" ", " "]]
            ]
        }
    }

    var defaultLayout = "en_GB";
    var layout = layouts[defaultLayout];
    var shiftPressed = false;
    var shiftLocked = false;
    var altPressed = false;
    var altLocked = false;

    window.onload = function() {
        buildKeyboard();
        document.getElementById("close").addEventListener('click', function() {
            sendText("exit");
	});
    }

    function buildKeyboard() {
        var keyboard = document.getElementById("keyboard");

        var rowTemplate = keyboard.getElementsByClassName("rowTemplate")[0];
        var rowParent = rowTemplate.parentNode;
        rowParent.removeChild(rowTemplate);

        for (var i in layout.keys) {
            var newRow = rowParent.appendChild(rowTemplate.cloneNode(true));

            var keyTemplate = newRow.getElementsByClassName("keyTemplate")[0];
            var keyParent = keyTemplate.parentNode;
            keyParent.removeChild(keyTemplate);

            for (var k in layout.keys[i]) {
                var key = layout.keys[i][k][0];
                var newKey = keyParent.appendChild(keyTemplate.cloneNode(true));

                if (key == " ") newKey.className += " space";
                else if (isControlKey(key)) newKey.className += " control";

                newKey.getElementsByTagName("span")[0].innerHTML = key;
                newKey.addEventListener('click', keyPress);
            }
        }
    }

    function modifyKeyboard(type) {
        switch(type) {
            case "reset":
                altPressed = altLocked = shiftPressed = shiftLocked = false;
                break;
            case "Alt":
            case "AltGr":
                altPressed = !altPressed;
                break;
            case "AltLk":
                altPressed = false;
                altLocked = !altLocked;
                break;
            case "Caps":
                shiftPressed = false;
                shiftLocked = !shiftLocked;
                break;
            case "Shift":
                shiftPressed = !shiftPressed;
                break;
        }

        var index = 0;
        if (!shiftPressed != !shiftLocked) index += 1;
        if (!altPressed != !altLocked) index += 2;

        for (var i in layout.keys) {
            var row = keyboard.getElementsByClassName("rowTemplate")[i];

            for (var k in layout.keys[i]) {
                var keySet = layout.keys[i][k];
                var key = (isControlKey(keySet[0])) ? keySet[0] : keySet[index] || "\xa0";

                var cell = row.getElementsByClassName("keyTemplate")[k];
                var text = cell.getElementsByTagName("span")[0];
                text.innerHTML = key;

                switch(keySet[0]) {
                    case "Alt":
                    case "AltGr":
                        text.className = altPressed ? "pressed" : "";
                        break;
                    case "AltLk":
                        text.className = altLocked ? "pressed" : "";
                        break;
                    case "Caps":
                        text.className = shiftLocked ? "pressed" : "";
                        break;
                    case "Shift":
                        text.className = shiftPressed ? "pressed" : "";
                        break;
                }
            }
        }
    }

    function keyPress(event) {
        var text = event.target.textContent;
        switch(text) {
            case "Caps":
            case "Shift":
            case "Alt":
            case "AltGr":
            case "AltLk":
                modifyKeyboard(text);
                break;
            case "Tab":
                sendText("Tab");
                break;
            case "Enter":
                sendText("Enter");
                break;
            case " ":
                sendText("Space");
                break;
            default:
                sendText(text);
                break;
        }
    }

    function sendText(text) {
        document.location.href = "#";
        document.location.href = "#key_" + text;
        if (shiftPressed) modifyKeyboard("Shift");
        if (altPressed) modifyKeyboard("AltGr");
    }

    function isControlKey(key) {
        return ~["Alt", "AltGr", "AltLk", "Caps", "Shift", "Tab", "Enter", "Bksp"].indexOf(key);
    }
})();
