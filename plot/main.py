import json
import glob
import matplotlib.pyplot as plt
import matplotlib

file_tests = open('data/tests.json')
tests_set = json.loads(file_tests.read())


def compare_algo(tests):
    dimension_dict = {}
    for test in tests:
        if test['dim'] not in dimension_dict.keys():
            dimension_dict[test['dim']] = {'name':[],'running_time':[], 'nb_evaluation':[],'merit':[]}
        name = test['name']
        for p in test['params']:
            name = name + ' ' + '\n' + p + '=' + str(test['params'][p])
        dimension_dict[test['dim']]['name'].append(name)
        dimension_dict[test['dim']]['running_time'].append(test['mean_time'])
        dimension_dict[test['dim']]['nb_evaluation'].append(max(test['nb_requests'],test['nb_atomic_swaps']))
        dimension_dict[test['dim']]['merit'].append(test['mean_merit'])
    for N in dimension_dict.keys():
        fig = plt.figure()
        for i in range(len(dimension_dict[N]['merit'])):
            plt.scatter(dimension_dict[N]['running_time'][i],
            dimension_dict[N]['merit'][i])
            plt.annotate(dimension_dict[N]['name'][i],
            (dimension_dict[N]['running_time'][i],
            dimension_dict[N]['merit'][i]))
        plt.xlabel('running time')
        plt.ylabel('merit')
        #fig.suptitle('Comparison in results and runtime of the different algorithm')
        #plt.show()
        fig.savefig('figure/compare_'+str(N)+'.png', dpi=fig.dpi, bbox_inches='tight')
        fig.savefig('figure/compare_'+str(N)+'.pdf', bbox_inches='tight')
        fig = plt.figure()
        for i in range(len(dimension_dict[N]['merit'])):
            plt.scatter(dimension_dict[N]['nb_evaluation'][i],
            dimension_dict[N]['merit'][i])
            plt.annotate(dimension_dict[N]['name'][i],
            (dimension_dict[N]['nb_evaluation'][i],
            dimension_dict[N]['merit'][i]))
        plt.xlabel('number of evaluation')
        plt.ylabel('merit')
        #fig.suptitle('Comparison in results and runtime of the different algorithm')
        #plt.show()
        fig.savefig('figure/compare_nb_eval_'+str(N)+'.png', dpi=fig.dpi, bbox_inches='tight')
        fig.savefig('figure/compare_nb_eval_'+str(N)+'.pdf', bbox_inches='tight')

def convergence_in_nb_step(tests):
    step_tests = [x  for x in tests if x['steps'] != {}]
    for test in step_tests:
        max_so_far = 0
        result = []
        for s in test['steps'].keys():
            max_so_far = max (max_so_far, test['steps'][s]['merit'])
            result.append(max_so_far)
        runtime = [ test['steps'][s]['time'] for s in test['steps']]
        merit = [ test['steps'][s]['merit'] for s in test['steps']]
        fig = plt.figure()
        plt.plot(runtime,merit,'#b2b2ff')
        plt.plot(runtime,result,'#0000ff')
        plt.xlabel('running time')
        plt.ylabel('merit')
        #fig.suptitle('Convergence of the algorithm ' + test['name'])
        #plt.show()
        fig.savefig('figure/convergence_'+test['name']+'.png', dpi=fig.dpi, bbox_inches='tight')
        fig.savefig('figure/convergence_'+test['name']+'.pdf', bbox_inches='tight')

def evolution_in_dimension(tests):
    algo_dict = {}
    for test in tests:
        if test['name'] not in algo_dict.keys():
            algo_dict[test['name']] = {'dimension':[],'running_time':[],'nb_evaluation':[], 'mean_merit':[],'max_merit':[]}
        else:
            algo_dict[test['name']]['dimension'].append(test['dim'])
            algo_dict[test['name']]['running_time'].append(test['mean_time'])
            algo_dict[test['name']]['nb_evaluation'].append(max(test['nb_requests'],test['nb_atomic_swaps']))
            algo_dict[test['name']]['mean_merit'].append(test['mean_merit'])
            algo_dict[test['name']]['max_merit'].append(test['merit'])
    fig = plt.figure()
    for algo in algo_dict.keys():
        plt.plot(algo_dict[algo]['dimension'],algo_dict[algo]['mean_merit'], label=algo)
    plt.xlabel('dimension')
    plt.ylabel('mean_merit')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    #fig.suptitle('Evolution of the mean-merit of the algorithms ' + '\n depending on the dimension', fontsize=12)
    fig.savefig('figure/dimension_mean_merit.png', dpi=fig.dpi, bbox_inches='tight')
    fig.savefig('figure/dimension_mean_merit.pdf', bbox_inches='tight')
    fig = plt.figure()
    for algo in algo_dict.keys():
        plt.plot(algo_dict[algo]['dimension'],algo_dict[algo]['max_merit'], label=algo)
    plt.xlabel('dimension')
    plt.ylabel('max_merit')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    #fig.suptitle('Evolution of the max-merit of the algorithms ' + '\n depending on the dimension', fontsize=12)
    fig.savefig('figure/dimension_max_merit'+'.png', dpi=fig.dpi, bbox_inches='tight')
    fig.savefig('figure/dimension_max_merit.pdf', bbox_inches='tight')
    fig = plt.figure()
    for algo in algo_dict.keys():
        plt.plot(algo_dict[algo]['dimension'],algo_dict[algo]['running_time'], label=algo)
    plt.xlabel('dimension')
    plt.ylabel('runtime')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    #fig.suptitle('Evolution of the mean-runtime of the algorithms ' + '\n depending on the dimension', fontsize=12)
    fig.savefig('figure/dimension_runtime'+'.png', dpi=fig.dpi, bbox_inches='tight')
    fig.savefig('figure/dimension_runtime'+'.pdf', dpi=fig.dpi, bbox_inches='tight')
    fig = plt.figure()
    for algo in algo_dict.keys():
        plt.plot(algo_dict[algo]['dimension'],algo_dict[algo]['nb_evaluation'], label=algo)
    plt.xlabel('dimension')
    plt.ylabel('number of evaluation')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    #fig.suptitle('Evolution of the number of evaluation of the algorithms ' + '\n depending on the dimension', fontsize=12)
    fig.savefig('figure/dimension_eval'+'.png', dpi=fig.dpi, bbox_inches='tight')
    fig.savefig('figure/dimension_eval'+'.pdf', dpi=fig.dpi, bbox_inches='tight')

def evolution_in_param(param, tests):
    param_dict = {param : [], 'running_time' : [], 'merit' : []}
    name = ''
    for test in tests:
        name = test['name']
        param_dict[param].append(test['params'][param])
        param_dict['running_time'].append(test['mean_time'])
        param_dict['merit'].append(test['mean_merit'])
    fig = plt.figure()
    plt.plot(param_dict[param],param_dict['merit'], label=param)
    plt.xlabel(param)
    plt.ylabel('merit')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    #fig.suptitle('Evolution of the merit of algorithm ' + name + '\n depending on the ' + param, fontsize=12)
    fig.savefig('figure/param_mean_merit_' + name + '_' + param + '.png', dpi=fig.dpi, bbox_inches='tight')
    fig.savefig('figure/param_mean_merit_' + name + '_' + param + '.pdf', dpi=fig.dpi, bbox_inches='tight')
    fig = plt.figure()
    plt.plot(param_dict[param],param_dict['running_time'], label=param)
    plt.xlabel(param)
    plt.ylabel('runtime')
    plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.12))
    #fig.suptitle('Evolution of the runtime of algorithm ' + name + '\n depending on the ' + param, fontsize=12)
    fig.savefig('figure/dimension_runtime_' + name + '_' + param + '.png', bbox_inches='tight')
    fig.savefig('figure/dimension_runtime_' + name + '_' + param + '.pdf', bbox_inches='tight')

for tests in tests_set:
    if tests['type'] == "compare":
        compare_algo(tests['dataset'])
        convergence_in_nb_step(tests['dataset'])
    if tests['type'] == "benchmark" and tests['abciss'] == "dim":
        evolution_in_dimension(tests['dataset'])
    elif tests['type'] == "benchmark":
        evolution_in_param(tests['abciss'],tests['dataset'])
