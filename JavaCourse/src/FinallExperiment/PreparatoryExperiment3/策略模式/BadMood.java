package FinallExperiment.PreparatoryExperiment3.策略模式;

public class BadMood extends Police {
    BadMood(){
        this.punish=new Ticket();
        this.talk=new DOnotTalk();
    }

    @Override
    void display() {
        punish.punish();
        talk.talk();
    }
}
