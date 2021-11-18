//
// Created by 12077 on 2021/6/29.
//

#include "hand.h"
Hand::Hand() {
    this->discardAll();
}

void Hand::discardAll() {
    this->curValue.soft= false;
    this->curValue.count=0;
}

void Hand::addCard(Card c) {
    if(this->curValue.soft){
        if(c.spot==ACE|| this->curValue.count>=21){
            this->curValue.count= this->curValue.count+1;
        } else{
            switch (c.spot) {
                case JACK:
                case QUEEN:
                case KING:
                    this->curValue.count+=10;
                    break;
                default:
                    this->curValue.count+=(c.spot+2);
                    break;
            }
            if(this->curValue.count>21){
                this->curValue.count= this->curValue.count-10;
                this->curValue.soft= false;
            }
        }
    } else{
       if(c.spot==ACE){
           this->curValue.count += 11;
           this->curValue.soft = true;
       } else{
           switch (c.spot) {
               case JACK:
               case QUEEN:
               case KING:
                   this->curValue.count+=10;
                   break;
               default:
                   this->curValue.count+=(c.spot+2);
                   break;
           }
           if(this->curValue.count>21&& this->curValue.soft){
               this->curValue.count= this->curValue.count-10;
               this->curValue.soft= false;
           }
    }
}}

HandValue Hand::handValue() const {
    return this->curValue;
}