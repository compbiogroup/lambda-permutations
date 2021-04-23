import os 

#probs = ['r','t','rt']
#for lamb in range (5, 101, 5):
#    for i in range(len(probs)):
#        cmd = './gen-lp-from-iota -n 100 -l ' + str(lamb) + ' -o 20 -q 1000 -a ' + probs[i] + ' > ~/pesquisa/instances/lambda-permutations-from-identity/unsigned/' + probs[i] + '/n100-1000/' + 'lamb'+str(lamb)+'-n100-1000.lp'
#        print(cmd)
#        os.system (cmd) 
#        cmd = './gen-lp-from-iota -n 100 -l ' + str(lamb) + ' -u 0 -o 20 -q 1000 -a ' + probs[i] + ' > ~/pesquisa/instances/lambda-permutations-from-identity/signed/' + probs[i] + '/n100-1000/' + 'lamb'+str(lamb)+'-n100-1000.lp'
#        print(cmd)
#        os.system (cmd) 
        
probs = ['r','t','rt']
for lamb in range (12, 12, 1):
    for i in range(len(probs)):
        cmd = './gen-lp-from-iota -n 100 -l ' + str(lamb) + ' -o 20 -q 1000 -a ' + probs[i] + ' > ~/pesquisa/instances/lambda-permutations-from-identity/unsigned/' + probs[i] + '/n100-1000/' + 'lamb'+str(lamb)+'-n100-1000.lp'
        print(cmd)
        os.system (cmd) 
        cmd = './gen-lp-from-iota -n 100 -l ' + str(lamb) + ' -u 0 -o 20 -q 1000 -a ' + probs[i] + ' > ~/pesquisa/instances/lambda-permutations-from-identity/signed/' + probs[i] + '/n100-1000/' + 'lamb'+str(lamb)+'-n100-1000.lp'
        print(cmd)
        os.system (cmd) 
        

