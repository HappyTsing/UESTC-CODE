package FinallExperiment.PreparatoryExperiment3.策略模式;

public class TanTan extends Police {
    TanTan(){
        this.punish=new Education();
        this.talk=new Talkshow();
    }

    @Override
    void display() {
        punish.punish();
        talk.talk();
    }
}
