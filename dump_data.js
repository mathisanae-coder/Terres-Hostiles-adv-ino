// Simulateur d'équilibrage : node sim.js (index.html et ia-simulateur.js dans le même dossier)
const fs=require('fs'),vm=require('vm');
const src=(h=>h.slice(h.lastIndexOf('<script>')+8,h.indexOf('</script>',h.lastIndexOf('<script>'))))(fs.readFileSync('/home/claude/work'+'/index.html','utf8'))+'\n'+fs.readFileSync('/home/claude/work'+'/ia-simulateur.js','utf8');
const el=()=>({innerHTML:'',style:{},dataset:{},classList:{add(){},remove(){}},appendChild(){},addEventListener(){},querySelector(){return null},remove(){},select(){},focus(){}});
const LSM={};const ctx={console,setTimeout,clearTimeout,setInterval:()=>0,clearInterval(){},Math,JSON,Date,Promise,
 localStorage:{getItem:k=>LSM[k]||null,setItem(k,v){LSM[k]=v}},navigator:{},
 document:{querySelector:()=>el(),getElementById:()=>el(),createElement:el,addEventListener(){},documentElement:{dataset:{},setAttribute(){},removeAttribute(){},hasAttribute(){return false}},body:el(),hidden:false},
 window:{addEventListener(){},scrollTo(){}},CompressionStream:undefined,RTCPeerConnection:function(){},btoa,atob,TextEncoder,TextDecoder,Uint8Array,Response,unescape,escape};
ctx.window.AudioContext=undefined;
vm.createContext(ctx);
vm.runInContext(src+`
;globalThis.T={DEFS,ENVS,WX,WX_TABLE,RECIPES,REMEDES,DIFF,SEASON_FX,SEASONS,SEASON_LEN,HAND_MAX,INV_MAX,SAT_MAX,EAU_MAX,ENE_MAX,SIGNAL_GOAL,EXPLORE_DRAWS,AP_COST,COND_DAYS,COND_LABEL,COND_TXT,RAW_RISK,CARRIERS,HAB_NAMES,AP_BASE,render,UI,makeRec,cleanSave,importSave,exportSave,loadSaves,dailyScenario,ptsOf,cleanCard,get UID(){return UID},set G(v){G=v},newGame,startPlayer,drawEnv,aiTurn,advice,humanNight,WX,ENVS,get G(){return G},nextTurn,stressNight};
`,ctx);

module.exports=ctx.T;
