import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtQml 2.2


ApplicationWindow {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Component {
        id: menuButtons

        ButtonStyle{
            background: Rectangle{
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.focus ? 2 : 1
                border.color: "green"
                radius: 4

            }
        }
    }

    /*Component{
        id: active_button

        ButtonStyle{
            background: Rectangle{
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.focus ? 2 : 1
                border.color: "red"
                radius: 4
                color: LinearGradient{
                    anchors.fill: parent
                    start: Qt.point(0,0)
                    end:Qt.point(parent.width,parent.height)
                }
            }
        }
    }*/

    Rectangle{
        id: root_win_welcome
        width: root.width
        height: root.height
        visible: true


        Column{
            anchors.centerIn: root_win_welcome

            Label{
                id: welcome_label_title
                text: "Tic Tic Tac Toe"
            }


            Button {
                id: welcome_button_startGame
                text: "Start Game "

                style: menuButtons



               onClicked: {
                    root_win_chooseMode.visible= true

                }
            }

            Button{
                id: welcome_button_highscore
                text: "Highscore"

                style: menuButtons




                onClicked: {
                    root_win_highscore.visible = true

                }
            }
        }

    }//end of win_welcome

    Rectangle{
        id: root_win_chooseMode
        width: root.width
        height: root.height
        visible: false

        Column{
            anchors.centerIn: root_win_chooseMode


            Label{
                text: "her velger man spille modus"
            }

            Button{
                id: chooseMode_button_pvp
                text: "Player vs Player"

                style: menuButtons

                onClicked: {
                    console.log("player v player selected")

                    root_win_chooseMode.visible = false
                    root_win_setPlayerName.pvp = true
                    root_win_setPlayerName.visible = true



                    //controller.testMethode();
                }
            }

            Button{
                id: chooseMode_button_pvc
                text: "Player vs Computer"

                style: menuButtons

                onClicked: {
                    console.log("player v computer selected")

                    root_win_chooseMode.visible = false
                    root_win_setPlayerName.pvp = false
                    root_win_setPlayerName.visible = true
                    setPlayerName_textField_namePlayer.forceActiveFocus()
                }
            }

            Button{
                id: chooseMode_button_back
                text: "Back"

                style: menuButtons

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

        Row{

            anchors.centerIn: parent
            property bool playerX: true


            Label {
                text: "name: "
            }

            TextField{

                id: setPlayerName_textField_namePlayer

            }

            Button{
                text: "OK"

                onClicked: {


                    if(parent.playerX){

                        crtObj.setPlayer(setPlayerName_textField_namePlayer.text,parent.playerX);
                        if(root_win_setPlayerName.pvp){
                            setPlayerName_textField_namePlayer.text="";
                            parent.playerX = false;
                            setPlayerName_textField_namePlayer.forceActiveFocus()
                        }else{
                            crtObj.setComputer();
                            root_win_setPlayerName.visible= false;
                            root_win_game.visible= true;
                            playerName_display.text= crtObj.getName_playerX();
                            setPlayerName_textField_namePlayer.text="";
                            canvas.x_playersTurn = true

                        }

                    }else{

                        console.log("hei")
                        crtObj.setPlayer(setPlayerName_textField_namePlayer.text,parent.playerX);
                        root_win_setPlayerName.visible= false;
                        setPlayerName_textField_namePlayer.text="";
                        root_win_game.visible= true;
                        playerName_display.text= crtObj.getName_playerX()+"s";
                        canvas.x_playersTurn = true


                    }

                    canvas.initiate = false;
                }


            }
            Button{

                text:"Back"

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
        color: "green";
        visible: false



        Column{


            ListView{
                width: root.width*0.5
                height: root.height*0.5


                model: Higscorelist{}

                delegate: Text{
                    text: name + " : " + points
                }
            }

            Button{
                text : "close"


                onClicked: {
                    root_win_highscore.visible = false
                }
            }
        }

        Column {
            Button{

                onClicked: {

                    crtObj.updateScoreInHighscore();
                    crtObj.showScoresFromHighscore();


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

                    Button{
                        text: "Menu"

                        onClicked: {
                            root_win_game.visible = false

                        }
                    }

                    Button{
                        text: "reset"
                        onClicked: {
                            /*for (var i = 0 ; i < canvas.board_one.length; i++){
                                for (var j = 0; j < canvas.board_one[0].length;j++){
                                    canvas.board_one[i][j]=0;
                                }
                            }*/

                            crtObj.clearBoard();
                            canvas.initiate = true;
                            canvas.requestPaint();
                            canvas.x_playersTurn = true;
                        }
                    }
                }//end of menu row


                Row{
                    id: centerColumn
                    width: parent.width
                    height: parent.height

                    Item{

                        Timer{
                            id : timer_endGame
                            interval: 1500;
                            running: false;
                            repeat: false;
                            onTriggered: win_gameEnded.visibility = "Windowed";

                        }
                    }

                    Window{
                        id : win_gameEnded
                        visibility: "Hidden"
                        modality: "WindowModal"
                        width: root_win_game.width*0.8

                        Column{
                            anchors.centerIn: parent

                            Label{
                                id: gameEnded_label
                            }

                            Row{

                                Button{
                                    text: "Play again"

                                    onClicked: {
                                        crtObj.clearBoard();
                                        canvas.initiate = true;
                                        canvas.requestPaint();
                                        canvas.x_playersTurn = true;
                                        win_gameEnded.visibility= "Hidden"
                                    }
                                }

                                Button{
                                    text: "end game"
                                }
                            }
                        }

                    }


                    Canvas{


                        property int board_x
                        property int board_y
                        property bool initiate: true
                        property bool x_playersTurn: true
                        property string cross: "resources/ttt_cross.gif"
                        property string sircles: "resources/ttt_sircle.gif"
                        Component.onCompleted: loadImage(cross),loadImage(sircles)

                        id:canvas

                        width: parent.width
                        height: parent.width

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

                                    if(crtObj.checkIfWon() || crtObj.checkIfDraw()){
                                        timer_endGame.running = true;
                                        if (crtObj.checkIfWon()){
                                            gameEnded_label.text = (crtObj.getWinnerName() + " is the winner");
                                        }else{
                                            gameEnded_label.text = "Its a draw";
                                        }

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

                                }else{

                                    //run error invalid move.

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

                    color: "red"

                    anchors.centerIn: parent

                    Column{
                        padding: 10

                        Label{
                            width: root_win_game*0.2
                            height: 30
                            color: "green"
                            //horizontalAlignment: AlignHCenter
                            text: "Its"
                        }

                        Label{
                            id : playerName_display

                        }

                        Label{
                            text: "turn"
                        }
                    }
                }

            }

        }//end of content row

    }//end of root_win_game

}//end of root




