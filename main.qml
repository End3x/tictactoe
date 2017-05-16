import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtQml 2.2
import QtQuick.Window 2.2




ApplicationWindow {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("Tic tac toe")

    Component {
        id: menuButtons_large

        ButtonStyle{
            background: Rectangle{
                implicitWidth: 200
                implicitHeight: 25
                border.width: control.focus ? 2 : 1
                border.color: "green"
                radius: 4
            }
        }
    }// end of menuButton_large

    Component {
        id: menuButtons_small

        ButtonStyle{
            background: Rectangle{
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.focus ? 2 : 1
                border.color: "green"
                radius: 4
            }
        }
    }// end of menuButton_small

    Rectangle{
        id: root_win_welcome
        width: root.width
        height: root.height
        visible: true

        Column{
            spacing: 10
            anchors.centerIn: root_win_welcome

            Label{
                id: welcome_label_title
                font.pointSize: 32
                text: "Tic Tac Toe"
            }

            Button {
                id: welcome_button_startGame
                text: "Start Game "
                style: menuButtons_small

                onClicked: {
                    root_win_chooseMode.visible= true
                }
            }

            Button{
                id: welcome_button_highscore
                text: "Highscore"
                style: menuButtons_small

                onClicked: {
                    root_win_highscore.visible = true

                }
            }
        }
    }//end of win_welcome

    Item{
        Timer{
            id: invalid_timer
            interval: 1500
            running: false
            repeat: false
            onTriggered: invalid_move_display.visible = false

        }
    }

    Rectangle{
        id: root_win_chooseMode
        width: root.width
        height: root.height
        visible: false

        Column{
            spacing: 10
            padding: 30
            anchors.centerIn: parent

            Label{
                font.pointSize: 32
                text: "Choose Mode"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Button{
                id: chooseMode_button_pvp
                text: "Player vs Player"
                style: menuButtons_large

                onClicked: {
                    root_win_chooseMode.visible = false
                    root_win_setPlayerName.pvp = true
                    root_win_setPlayerName.visible = true
                }
            }

            Button{
                id: chooseMode_button_pvc
                text: "Player vs Computer"
                style: menuButtons_large

                onClicked: {
                    root_win_chooseMode.visible = false
                    root_win_setPlayerName.pvp = false
                    root_win_setPlayerName.visible = true
                    setPlayerName_textField_namePlayer.forceActiveFocus()
                }
            }

            Button{
                id: chooseMode_button_back
                text: "Back"
                style: menuButtons_small

                onClicked: {
                    root_win_chooseMode.visible = false
                }
            }
        }
    }//end of win_chooseMode

    Rectangle{
        id: root_win_setPlayerName
        width: root.width
        height: root.height
        visible: false

        property bool pvp: false
        property string input: ""

        Column{
            anchors.centerIn: parent
            property bool playerX: true
            spacing: 10

            TextField{
                id: setPlayerName_textField_namePlayer
                width: 200
                placeholderText: "Name : Player X"
            }

            Button{
                text: "OK"
                style: menuButtons_small

                onClicked: {
                    if(parent.playerX){
                        crtObj.setPlayer(setPlayerName_textField_namePlayer.text,parent.playerX);
                        if(root_win_setPlayerName.pvp){
                            setPlayerName_textField_namePlayer.placeholderText = "Name : Player O"
                            setPlayerName_textField_namePlayer.text="";
                            parent.playerX = false;
                            setPlayerName_textField_namePlayer.forceActiveFocus()
                        }else{
                            crtObj.setComputer();
                            root_win_setPlayerName.visible= false;
                            root_win_game.visible= true;
                            playerName_display.text= (crtObj.getName_playerX()+"s");
                            setPlayerName_textField_namePlayer.text="";
                            canvas.x_playersTurn = true
                        }

                    }else{
                        crtObj.setPlayer(setPlayerName_textField_namePlayer.text,parent.playerX);
                        root_win_setPlayerName.visible= false;
                        setPlayerName_textField_namePlayer.text="";
                        root_win_game.visible= true;
                        playerName_display.text= crtObj.getName_playerX()+"s";
                        canvas.x_playersTurn = true
                    }

                    canvas.initiate = false;
                    highscore_button_continue.visible = true

                }
            }

            Button{

                text:"Back"
                style: menuButtons_small

                onClicked: {
                    root_win_chooseMode.visible = true;
                    root_win_setPlayerName.visible= false;
                }
            }
        }
    }//end of root_win_setPlayerName

    Rectangle{
        id: root_win_highscore
        height: root.height
        width: root.width
        visible: false

        onVisibleChanged: {
            if (visible == true){
                higscorelist.clear();

                for (var i = 0 ; i < 5 ; i++){

                    if (crtObj.getHighscoreEntriesNames(i) !== "" && crtObj.getHighscoreEntriesScore(i) !== -1){
                        higscorelist.append({
                                                name: crtObj.getHighscoreEntriesNames(i),
                                                score: crtObj.getHighscoreEntriesScore(i)
                                            })
                    }
                }
            }
        }

        Rectangle{
            width: root.width*0.5
            height: root.height*0.5
            anchors.centerIn: parent

            Column{
                anchors.verticalCenter: parent.verticalCenter

                ListView{
                    width: root.width*0.5
                    height: root.height*0.3
                    model: higscorelist

                    delegate: Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: name + "    " + score
                        font.pointSize: 18

                    }
                }

                ListModel{
                    id: higscorelist

                }

                Button{
                    id: highscore_button_btm
                    text : "Back to menu"
                    style: menuButtons_small
                    anchors.horizontalCenter: parent.horizontalCenter

                    onClicked: {
                        root_win_highscore.visible = false
                        highscore_button_continue.visible = false
                    }
                }

                Button{
                    id : highscore_button_continue
                    text: "Continue game"
                    visible: false
                    style: menuButtons_small
                    anchors.horizontalCenter: parent.horizontalCenter

                    onClicked: {
                        root_win_highscore.visible = false

                        root_win_game.visible = true
                    }
                }
            }
        }
    }//end of root_win_highscore


    Rectangle{

        id:root_win_game
        width: root.width
        height: root.height
        visible: false

        Row{
            width: parent.width
            height: parent.height

            Column{
                width: parent.width*0.20
                height: parent.height

            }

            Column{
                id: menu_column
                width: root.width*0.6
                height: root.height

                Row{
                    height: parent.height*0.15
                    spacing: 10
                    padding: 30

                    Button{
                        text: "Quit game"
                        style: menuButtons_small

                        onClicked: {
                            root_win_game.visible = false
                            canvas.initiate = true;
                            canvas.requestPaint();
                            canvas.x_playersTurn = true;
                            highscore_button_continue.visible = false
                            highscore_button_close.visible = true
                        }
                    }

                    Button{
                        text: "Restart game"
                        style: menuButtons_small

                        onClicked: {
                            crtObj.clearBoard();
                            canvas.initiate = true;
                            canvas.requestPaint();
                            canvas.x_playersTurn = true;
                        }
                    }

                    Button{
                        id: root_button_highscore
                        text: "Highscore"
                        style: menuButtons_small

                        onClicked: {
                            root_win_highscore.visible = true
                            root_win_game.visible = false
                        }
                    }
                }


                Row{
                    id: centerColumn
                    width: parent.width
                    height: parent.height

                    Window{
                        id : win_gameEnded
                        visibility: "Hidden"
                        modality: "WindowModal"
                        width: root_win_game.width*0.8

                        Column{
                            anchors.centerIn: parent

                            Label{
                                id: gameEnded_label
                                anchors.centerIn: parent
                            }

                            Row{
                                spacing: 10
                                padding: 30

                                Button{
                                    text: "Play again"
                                    style: menuButtons_small

                                    onClicked: {
                                        crtObj.clearBoard();
                                        canvas.initiate = true;
                                        canvas.requestPaint();
                                        canvas.x_playersTurn = true;
                                        win_gameEnded.visibility= "Hidden"
                                    }
                                }

                                Button{
                                    text: "Back to Menu"
                                    style: menuButtons_small

                                    onClicked: {
                                        win_gameEnded.visibility= "Hidden"
                                        root_win_game.visible = false
                                        canvas.initiate = true;
                                        canvas.requestPaint();
                                        canvas.x_playersTurn = true;
                                        highscore_button_continue.visible = false

                                    }
                                }
                            }
                        }
                    }

                    Canvas{
                        id:canvas
                        width: parent.width
                        height: parent.width

                        property int board_x
                        property int board_y
                        property bool initiate: true
                        property bool x_playersTurn: true
                        property string cross: "resources/ttt_cross.gif"
                        property string sircles: "resources/ttt_sircle.gif"

                        Component.onCompleted: loadImage(cross),loadImage(sircles)

                        MouseArea{
                            id:mouse_area
                            anchors.fill: parent

                            onPressed: {
                                canvas.initiate= false

                                if(crtObj.setMove(mouseX/(canvas.width/3), mouseY/(canvas.height/3), canvas.x_playersTurn)){
                                    canvas.requestPaint();

                                    if (playerName_display.text === (crtObj.getName_playerX()+"s")){
                                        playerName_display.text = crtObj.getName_playerO()+"s";

                                    }else{
                                        playerName_display.text = crtObj.getName_playerX()+"s";

                                    }

                                    if (!root_win_setPlayerName.pvp){

                                        crtObj.setComputerMove();
                                        canvas.requestPaint();

                                    }else{
                                        if (canvas.x_playersTurn){
                                            canvas.x_playersTurn = false
                                        }else{
                                            canvas.x_playersTurn = true
                                        }
                                    }

                                    if(crtObj.checkIfWon() || crtObj.checkIfDraw()){
                                        win_gameEnded.visibility = "Windowed"
                                        if (crtObj.checkIfWon()){
                                            gameEnded_label.text = (crtObj.getWinnerName() + " is the winner");
                                        }else{
                                            gameEnded_label.text = "Its a draw";
                                        }
                                    }


                                }else{
                                    invalid_move_display.visible = true
                                    invalid_timer.start()
                                }
                            }
                        }

                        onPaint: {
                            var gc = getContext('2d');

                            if(initiate){
                                console.log("initiating")
                                playerName_display.text = crtObj.getName_playerX()+"s";

                                gc.fillStyle = "gray";
                                gc.fillRect(0, 0,canvas.width,canvas.height)
                                initiate = false;

                                gc.strokeStyle = "black";
                                gc.lineWidth = 1;
                                gc.beginPath()

                                gc.moveTo(canvas.width/3,0)
                                gc.lineTo(canvas.width/3,canvas.height)

                                gc.moveTo(2*canvas.width/3,0)
                                gc.lineTo(2*canvas.width/3,canvas.height)

                                gc.moveTo(0,0)
                                gc.lineTo(0,canvas.height)

                                gc.moveTo(canvas.width,0)
                                gc.lineTo(canvas.width,canvas.height)


                                gc.moveTo(0,canvas.height/3)
                                gc.lineTo(canvas.width,canvas.height/3)

                                gc.moveTo(0,2*canvas.height/3)
                                gc.lineTo(canvas.width,2*canvas.height/3)

                                gc.moveTo(0,0)
                                gc.lineTo(canvas.width,0)

                                gc.moveTo(0,canvas.height)
                                gc.lineTo(canvas.width,canvas.height)

                                gc.stroke();

                            }

                            else{



                                for( var i = 0 ; i < 3; i++){
                                    for( var j = 0 ; j < 3 ; j++){
                                        if (crtObj.getBoardArray(i,j) === 1){
                                            gc.drawImage(cross, i*(canvas.width/3), j*(canvas.height/3),canvas.width/3,canvas.height/3)
                                        }
                                        else if(crtObj.getBoardArray(i,j) === -1){
                                            gc.drawImage(sircles, i*(canvas.width/3), j*(canvas.height/3),canvas.width/3,canvas.height/3)
                                        }
                                    }
                                }

                                if(crtObj.checkIfWon()){

                                    gc.strokeStyle = "purple";
                                    gc.lineJoin = "round";
                                    gc.lineWidth = 15;
                                    gc.beginPath();


                                    if (crtObj.getWinnerDirection() === 0){
                                        gc.moveTo(canvas.width/6, crtObj.getWinnerSet() * canvas.height/3+ canvas.width/6);
                                        gc.lineTo(canvas.width - canvas.width/6, crtObj.getWinnerSet()*canvas.height/3 + canvas.width/6);
                                        console.log("winner is horizontal")

                                    }else if (crtObj.getWinnerDirection() === 1){
                                        gc.moveTo(crtObj.getWinnerSet() * canvas.height/3+ canvas.width/6, canvas.width/6 );
                                        gc.lineTo(crtObj.getWinnerSet()*canvas.height/3 + canvas.width/6, canvas.width - canvas.width/6);
                                        console.log("winner is vertical")

                                    }else{
                                        if( crtObj.getWinnerSet()=== 0){
                                            gc.moveTo(canvas.width/6, canvas.width/6)
                                            gc.lineTo( 2*canvas.height/3 + canvas.width/6, canvas.width - canvas.width/6)
                                            console.log("winner is diagonal")
                                        }else{
                                            gc.moveTo(  canvas.width/6, canvas.height - canvas.width/6 )
                                            gc.lineTo( canvas.width - canvas.width/6, canvas.width/6)
                                        }
                                    }

                                    gc.stroke();

                                }

                                /*if(canvas.x_playersTurn){

                                    canvas

                                    console.log("drawing X")
                                    canvas.x_playersTurn = false

                                }else{
                                    gc.drawImage(sircles, canvas.board_x*(canvas.width/3), canvas.board_y*(canvas.height/3),canvas.width/3,canvas.height/3)
                                    console.log("drawing O")
                                    canvas.x_playersTurn = true;
                                }*/



                                //gc.fillRect(canvas.board_x*(canvas.width/3), canvas.board_y*(canvas.height/3),canvas.width/3,canvas.height/3)
                            }

                        }//end of onPaint

                    }//end og Canvas

                }//end of center row

            }//end of content column

            Column{
                width: parent.width*0.20
                height: parent.height

                Rectangle{
                    width: parent.width
                    height: parent.height
                    // anchors.verticalCenter: parent.verticalCenter

                    Column{
                        width: parent.width
                        height: parent.height*0.15
                        padding: 10
                        anchors.verticalCenter: parent.verticalCenter




                        Label{
                            id : playerName_display
                            font.bold: true
                            font.pointSize: 24
                            anchors.horizontalCenter: parent.horizontalCenter

                        }

                        Label{
                            text: "turn"
                            font.pointSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                        }


                        Label{
                            id: invalid_move_display
                            text: "INVALID MOVE"
                            color: "red"
                            visible: false
                            font.pointSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }

            }

        }//end of content row

    }//end of root_win_game

}//end of root




