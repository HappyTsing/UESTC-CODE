package FinallExperiment.PreparatoryExperiment3.策略模式;

public class GoodMood extends Police {
    GoodMood(){
        this.punish=new Education();
        this.talk=new DOnotTalk();
    }

    @Override
    void display() {
        punish.punish();
        talk.talk();
    }
}
