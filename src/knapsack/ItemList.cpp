#include "ItemList.h"

void ItemList::populateList(){
    // for each gene in chromosome
    for (int i = 0; i < maxItems; ++i) {
        list.push_back(new Item(rValue(engine), rWeight(engine)));
//        std::cout << list.at(i)->getValue() << "\t"
//                  << list.at(i)->getWeight() << endl;
    }
}

// based on maxKnapsackWeight = 50kg
void ItemList::populateTestList(){
    list.push_back(new Item(6, 5));
    list.push_back(new Item(12, 7));
    list.push_back(new Item(17, 11));
    list.push_back(new Item(50, 32));
    list.push_back(new Item(75, 45));
}

void ItemList::printList(){
    std::cout << "---- ITEMS IN LIST ----" << endl;
    for (int item = 0; item < maxItems; ++item) {
        std::cout << item << ":\t";
        std::cout << "€" << list.at(item)->getValue()
                  << "\t\t" << list.at(item)->getWeight() << "kg"
                  << endl;
    }
}

Population* ItemList::calcPopulationFitness(Population *pop)
{
    double bestFitness = 0;
    double fitness, calculatedWeight;
    double totalValue, totalWeight;
    bool overweightFlag = false;
    vector<int> temp;

    for (Chromosome* x : pop->getPopulation()){
        do{
            totalValue = totalWeight = fitness = 0;
            overweightFlag = false;
            for (int i = 0; i < maxItems; ++i) {
                // if item selected in individual
                if(x->getGene(i) == 1){
                    // add value and weight to total
                    totalValue += list.at(i)->getValue();
                    totalWeight += list.at(i)->getWeight();
                    temp.push_back(i);
                    if(totalWeight > maxKnapsackWeight){
                        overweightFlag = true;
                        break;
                    }
                }
            }

            if (overweightFlag){
                // randomize chromosome
                x->removeItemFromChromosome();
            }else{
                // fitness function
                // Since weight is the priority, it is assigned a weighting of '2',
                // while value is assigned a weighting of '1'
//        fitness = 2*(1/(1+fabs(maxKnapsackWeight - totalWeight))) + 1*(1/(1+maxValueOfItemList-totalValue));
//                fitness = 2*(1/(1+fabs(maxKnapsackWeight - totalWeight))) + 1*(1/(totalValue));

                fitness = totalValue;

                if(bestFitness < fitness){
                    bestChromLog.chrom = x;
                    bestChromLog.maxValue = totalValue;
                    bestChromLog.maxWeight = totalWeight;
                    bestChromLog.itemList = temp;
                }
                temp.clear();
                x->setFitness(fitness);
            }
        }while(overweightFlag);
    }
    vector<int>().swap(temp); // clear allocated memory
    return pop;
}


void ItemList::printBestChromosomeLog()
{
    cout << "Best chromosome" << endl;
    cout << "Chromosome " << bestChromLog.chrom
         << " - value: " << bestChromLog.maxValue
         << " - weight: " << bestChromLog.maxWeight << endl;
    cout << "Items selected: ";
    for (int i : bestChromLog.itemList){
        cout << i << " ";
    }
    cout << endl;
}


void ItemList::calculateMaxValue() {
    maxValueOfItemList = 0;
    for (Item* i : list){
        maxValueOfItemList += i->getValue();
    }
}




























// page break (lmao)